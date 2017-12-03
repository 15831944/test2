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
			//清空双链表
			void ClearLink();
			
			//销毁双链表
			void DestoryLink();

			//打印双链表
			void PrintLink();

			//在双链表末尾添加节点
			bool AppendLink(T e);

			//获取双链表的长度
			int Length();

			//在第pos个位置插入新节点
			bool InsertLink(int pos , T e);

			//删除第i个置上的节点
			bool DeleteNode(int pos);

			//删除指定元素的节点
			bool DeleteNode(T e);
		};

		//////////////////////////////////////////////////////////////////////////
		//
	}
}
#endif