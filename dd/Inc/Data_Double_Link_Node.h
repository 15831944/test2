#ifndef __DATA_DOUBLE_LINK_NODE_H__
#define __DATA_DOUBLE_LINK_NODE_H__

#define	DIRNAME_MAX_LEN		32
#define DIRPATH_MAX_LEN		256	

typedef struct tagDirDataStruct{
	char			szDirName[DIRNAME_MAX_LEN];
	char			szDirPath[DIRPATH_MAX_LEN];
	v_uint32_t		uIndex;
}DIR_DATA_STRUCT;

typedef struct tagDirNodeStruct{
	DIR_DATA_STRUCT		dirdata;
	struct tagDirStruct	*prev;
	struct tagDirStruct	*next;
}DIR_NODE_STRUCT;

DIR_NODE_STRUCT* create_double_link_node(DIR_DATA_STRUCT* pNodeData);

void  delete_all_double_link_node(DIR_NODE_STRUCT** pDLinkNode);


#endif