#ifdef COMFACESDK_EXPORTS
#define COMFACESDK_API __declspec(dllexport)
#else
#define COMFACESDK_API __declspec(dllimport)
#endif
#include <io.h>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

DECLARE_HANDLE(COM_HANDLE);
#define FEATURE_SIZE 1024

typedef struct{
    unsigned int uid;
	unsigned char feature[FEATURE_SIZE];
} FeaModel;

typedef struct{
	unsigned int uid;
	float score;
} MatchNode;


class COMFACESDK_API CComFaceSDK {
public:

	CComFaceSDK(void);

	//Summary: 比较两张照片的相似度
	//Parameters:
	//       imgPath1:照片1路径.
	//       imgPath2:照片2路径.
	//Return : 相似度
	float Compare2Image(char* imgPath1, char* imgPath2);

	//Summary: 比较两张照片的相似度
	//Parameters:
	//       imgBuffer1:照片1内存区.
	//       imgBuffer1Length:照片1内存区长度.
	//       imgBuffer2:照片2内存区.
	//       imgBuffer2Length:照片2内存区长度.
	//Return : 相似度
	float Compare2Image(unsigned char* imgBuffer1,int imgBuffer1Length, unsigned char* imgBuffer2,int imgBuffer2Length);
	
	//Summary: 比较两个人脸的相似度
	//Parameters:
	//       uid1:照片1编号.
	//       uid2:照片2编号.
	//Return : 相似度
	float Compare2Uid(unsigned int uid1, unsigned int uid2);


	//Summary: 注册人脸
	//Parameters:
	//       uid:人脸uid，这个需要在sdk外部自己定义.
	//       imgPath:照片路径.
	//Return : 0 表示成功，其他表示失败
	int Data_Insert(unsigned int uid, char* imgPath);

	//Summary: 注册人脸
	//Parameters:
	//       uid:人脸uid，这个需要在sdk外部自己定义.
	//       imgBuffer:照片内存区.
	//       imgBufferLength:照片内存区长度.
	//Return : 0 表示成功，其他表示失败
	int Data_Insert(unsigned int uid, unsigned char* imgBuffer,int imgBufferLength);


	//Summary: 搜索相似脸
	//Parameters:
	//       imgPath:照片路径.
	//       matchNode: 最相似结果.
	//Return : 0 表示成功，其他表示失败
	int Face_Search(char* imgPath, MatchNode &matchNode);

	//Summary: 搜索相似脸
	//Parameters:
	//       uid:人脸uid，这个需要在sdk外部自己定义
	//       matchNode: 最相似结果.
	//Return : 0 表示成功，其他表示失败
	int Face_Search(unsigned int uid, MatchNode &matchNode);

	//Summary: 搜索相似脸
	//Parameters:
	//       imgPath:照片路径.
	//       matchNodeArray:返回最相似的人脸结果数组，即top retNum.
	//       retNum:按照相似度降序排序，返回最相似的人脸个数.
	//Return : 0 表示成功，其他表示失败
	int Face_Search(char* imgPath, MatchNode* matchNodeArray, int retNum);


	//Summary: 搜索相似脸
	//Parameters:
	//       uid:人脸编号.
	//       matchNodeArray:返回最相似的人脸结果数组，即top retNum.
	//       retNum:按照相似度降序排序，返回最相似的人脸个数.
	//Return : 0 表示成功，其他表示失败
	int Face_Search(unsigned int uid, MatchNode* matchNodeArray, int retNum);


	//Summary: 比较两张照片的相似度
	//Parameters:
	//       imgBuffer:照片内存区.
	//       imgBufferLength:照片内存区长度.
	//       matchNodeArray:返回最相似的人脸结果数组，即top retNum.
	//       retNum:按照相似度降序排序，返回最相似的人脸个数.
	//Return : 0 表示成功，其他表示失败
	int Face_Search(unsigned char* imgBuffer,int imgBufferLength, MatchNode* matchNodeArray, int retNum);


	//Summary: 查找uid是否在人脸库中出现过
	//Parameters:
	//       uid:注册人脸时的uid.
	//Return : 0 表示成功，其他表示失败
	int Data_Search(unsigned int uid);

	//Summary:删除uid的人脸数据
	//Parameters:
	//       uid:注册人脸时的uid.
	//Return : 0 表示成功，其他表示失败
	int Data_Delete(unsigned int uid);

	//Summary: 清空所有注册的人脸数据
	//Parameters:
	//Return : void
	int Data_Clear();

	//Summary: 获取目前已经注册的人脸特征个数
	//Parameters:
	//Return : 人脸特征个数
	int Data_GetSize();

private:
	int _face_num;
	char _db_file[MAX_PATH];
private:
	void Data_Initial();
	void Data_Load();
	void Data_AppendOne(FeaModel fm);


private:
	COM_HANDLE _handler;
	BOOL _Initialed;
	vector<FeaModel> _feaPool;
	char _version[MAX_PATH];
	HMODULE _handleLib;
};

