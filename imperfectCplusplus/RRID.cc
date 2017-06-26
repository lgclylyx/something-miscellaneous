/*
 * RRID : resource release is(at) destruction
 * ����c++���Զ���ȷ����������֧�֣���ȷ��ĳ��װ���͵�ʵ�����������ԴҲ�ܹ��õ�ȷ���Ե��ͷ�
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
 * class ResourceManager��������ʹ��ָ���ķ����ͷ�ָ���������е���Դ
 */
class ResourceManager{
private:
	typedef std::vector<Resource*> resource_t;
	typedef sequence_container_veneer<resource_t,RelResource> resource_vec_rridt;

	resource_vec_rridt m_resources;
};
