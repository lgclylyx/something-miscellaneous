/*
一个时间轮，仿照Linux内核中的做法，将一个32位的超时
时长分割成5个hash队列。将定时器事件按照超时时间挂载
入相应的队列中。每一个周期处理最低级队列中的一个队列，
并且可能把更高层的队列重新hash到低一层的相应队列中。
*/

package main

import (
	"errors"
	"time"
	"fmt"
	"math/rand"
	"sync"
)

const (
	firstLen = 1 << 8
	secondLen = 1 << 6
	thirdLen = 1 << 6
	fourthLen = 1 << 6
	fifthLen = 1 << 6
	Len = 5
)

type TimeNode struct {
	next *TimeNode
	stopTime time.Time
	expire uint32
}

var (
	first [firstLen]*TimeNode
	second [secondLen]*TimeNode
	third [thirdLen]*TimeNode
	fourth [fourthLen]*TimeNode
	fifth [fifthLen]*TimeNode
	pos [Len]uint32 // pos[i]代表队列i中已经被处理过的哈希队列的位置
	num = 0
)

func init() {
	rand.Seed(time.Now().UnixNano())
}

func add(expireTime uint32, stopTime *time.Time) (bool, error) {
	node := new(TimeNode)
	if stopTime != nil {
		node.stopTime = *stopTime
	}

	node.expire = expireTime
	if insertNode := expireTime & 0xFC000000; insertNode != 0 {
		insertNode >>= 26;
		insertNode = (insertNode + pos[4]) % (1 << 6)
		fmt.Printf("insert a timer into queue fifth pos: %d\n", insertNode)
		node.next = fifth[insertNode]
		fifth[insertNode] = node
	} else if insertNode:= expireTime & 0x03F00000; insertNode != 0 {
		insertNode >>= 20
		insertNode = (insertNode + pos[3]) % (1 << 6)
		fmt.Printf("insert a timer into queue fourth pos: %d\n", insertNode)
		node.next = fourth[insertNode]
		fourth[insertNode] = node
	} else if insertNode := expireTime & 0x000FC000; insertNode != 0 {
		insertNode >>= 14
		insertNode = (insertNode + pos[2]) % (1 << 6)
		fmt.Printf("insert a timer into queue third pos: %d\n", insertNode)
		node.next = third[insertNode]
		third[insertNode] = node
	} else if insertNode := expireTime & 0x00003F00; insertNode != 0 {
		insertNode >>= 8
		insertNode = (insertNode + pos[1]) % (1 << 6)
		fmt.Printf("insert a timer into queue second pos: %d\n", insertNode)
		node.next = second[insertNode]
		second[insertNode] = node
	} else if insertNode := expireTime & 0x000000FF; insertNode != 0 {
		insertNode = (insertNode + pos[0]) % (1 << 8)
		fmt.Printf("insert a timer into queue first pos: %d\n", insertNode)
		node.next = first[insertNode]
		first[insertNode] = node
	} else {
		return false, errors.New("wrong expire")
	}
	return true, nil
}

func processQueue() {
	if pos[0] = (pos[0] + 1) % 256; pos[0] == 0 {
		if pos[1] = (pos[1] + 1) % 64; pos[1] == 0 {
			if pos[2] = (pos[2] + 1) % 64; pos[2] == 0 {
				if pos[3] = (pos[3] + 1) % 64; pos[3] == 0 {
					if pos[4] = (pos[4] + 1) % 64; pos[4] == 0 {
						fmt.Printf("long long ago, a timer started...\n")
					}
					for node := fifth[pos[4]]; node != nil; node = node.next {
						add(node.expire - (1 << 26), &node.stopTime)
					}
					fifth[pos[4]] = nil
				}
				for node := fourth[pos[3]]; node != nil; node = node.next {
					add(node.expire - (1 << 20), &node.stopTime)
				}
				fourth[pos[3]] = nil
			}
			for node := third[pos[2]]; node != nil; node = node.next {
				add(node.expire - (1 << 14), &node.stopTime)
			}
			third[pos[2]] = nil
		}
		for node := second[pos[1]]; node != nil; node = node.next {
			add(node.expire - (1 << 8), &node.stopTime)
		}
		second[pos[1]] = nil
	}
	count := 0
	for node := first[pos[0]]; node != nil; node = node.next {
		fmt.Printf("expire should at %vs, really at %v... \n", node.stopTime, time.Now())
		count++
	}
	first[pos[0]] = nil
	num += 1
	if count > 0 {
		fmt.Printf("%d : at %v, %d timer expire... \n", num, time.Now(), count)
	}
}

func timeClock(wg *sync.WaitGroup) {
	defer wg.Done()

	count := 0
	t := time.NewTicker(1 * time.Second)
	for {
		select {
		case <-t.C:
			processQueue()
			count++
		}
	}
}

func main() {
	var wg sync.WaitGroup
	for i := 1; i <= 10; i++ {
		now := time.Now()
		passSecond := rand.Int31n(100)+200
		expire := now.Add(time.Duration(passSecond) * time.Second)
		fmt.Printf("a event %d should expire at passed %vs\n", i, uint32(expire.Sub(now)/time.Second))
		add(uint32(expire.Sub(now)/time.Second), &expire)
	}

	wg.Add(1)
	go timeClock(&wg)

	wg.Wait()
}

