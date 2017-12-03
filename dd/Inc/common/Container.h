#ifndef __CONTAINER_H__
#define __CONTAINER_H__

using namespace std;
namespace Leaf
{
	namespace Container
	{
		template <typename T>struct node{
			T data;
			node<T> *prior;
			node<T>	*next;
		};

		template <typename T> class nLink
		{
		private:
			node<T> *head;

		public:
			nLink();
			~nLink();	

		public:
			//���˫����
			void ClearLink();
			
			//����˫����
			void DestoryLink();

			//��ӡ˫����
			void PrintLink();

			//��˫����ĩβ��ӽڵ�
			bool AppendLink(T e);

			//��ȡ˫����ĳ���
			int Length();

			//�ڵ�pos��λ�ò����½ڵ�
			bool InsertLink(int pos , T e);

			//ɾ����i�����ϵĽڵ�
			bool DeleteNode(int pos);

			//ɾ��ָ��Ԫ�صĽڵ�
			bool DeleteNode(T e);
		};

		//////////////////////////////////////////////////////////////////////////
		//
	}
}
#endif