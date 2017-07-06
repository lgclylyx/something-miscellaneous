#pragma once

class RCObject{
public:
	RCObject();
	RCObject(const RCObject& rhs);
	const RCObject& operator=(const RCObject& rhs);
	virtual ~RCObject()=0;
	void addReference();
	void removeReference();
	void markUnshareable();
	bool isShareable()const;
	bool isShared()const;
private:
	int refCount;
	bool shareable;
};
RCObject::RCObject():refCount(0),shareable(true){

}
RCObject::RCObject(const RCObject& rhs):refCount(0),shareable(true){

}
const RCObject& RCObject::operator=(const RCObject& rhs){
	return *this;
}
RCObject::~RCObject(){

}
void RCObject::addReference(){
	++refCount;
}
void RCObject::removeReference(){
	if(--refCount==0)
		delete this;
}
void RCObject::markUnshareable(){
	shareable=false;
}
bool RCObject::isShareable()const{
	return shareable;
}
bool RCObject::isShared()const{
	return refCount>1;
}