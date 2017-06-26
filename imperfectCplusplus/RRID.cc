/*
 * RRID : resource release is(at) destruction
 * 利用c++对自动的确定性析构的支持，来确保某封装类型的实例相关联的资源也能够得到确定性的释放
 */

class Resource;
void del_Resource(Resource*);

struct RelResource{
	void operator()(Resource *r){
		del_Resource(r);
	}
};

template<typename C,typename F>
class sequence_container_veneer:public C{
public:
	~sequence_container_veneer(){
		std::for_each(begin(),end(),F());
	}
};
/*
 * class ResourceManager的作用是使用指定的方法释放指定的容器中的资源
 */
class ResourceManager{
private:
	typedef std::vector<Resource*> resource_t;
	typedef sequence_container_veneer<resource_t,RelResource> resource_vec_rridt;

	resource_vec_rridt m_resources;
};
