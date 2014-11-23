#include "stdafx.h"
#include <atlimage.h>
#include <Windows.h>
#include "FaceSDK/ComFaceSDK.h"
#pragma comment(lib,"FaceSDK/ComFaceSDK.lib")


//SDK示例程序，1:1直接输入两个图片得路径即可比对
//1：N，需要提前把N注册到人像库中（SDK内部自己维护），使用Data_Insert函数接口
int _tmain(int argc, _TCHAR* argv[])
{
    //初始化
	CComFaceSDK* FaceAPI = new CComFaceSDK();

	char imgPath1[] = "1.jpg";
	char imgPath2[] = "2.jpg";

	//清空已经注册的所有数据，清零
	//FaceAPI->Data_Clear();

	//比较两张照片的相似度
	float score = FaceAPI->Compare2Image(imgPath1,imgPath2);
	printf("similar=%f\n", score);

	getchar();
	return 0;

	int uid1 = 4,uid2 = 6;//确保 uid1，uid2 已经在注册过
	score = FaceAPI->Compare2Uid(uid1,uid2);
	printf("similar=%f\n",score);

	//注册一张人脸
	//int ret = FaceAPI->Data_Insert(0,imgPath1);

	//删除uid=2的数据（人脸数据）
	//FaceAPI->Data_Delete(2);

	//批量注册照片，uid是外部唯一编号，有应用程序自行控制，sdk内部不做唯一性校验
	char filepath[MAX_PATH];
	//for (int i =1 ; i <= 6; i++)
	//{
	//	sprintf_s(filepath,"F:\\tmp\\face\\%d.jpg",i);
	//	CImage image;
	//	HRESULT hResult = image.Load(filepath);
	//	if(hResult != S_OK || image.IsNull())
	//	{
	//		printf("%s failed\n",filepath);//
	//		continue;
	//	}
	//	int ret = FaceAPI->Data_Insert(i,filepath);
	//	printf("ret = %d, %s\n",i,filepath);
	//}


	//人脸搜索

	//搜索最相似人脸数据
	MatchNode mn;
	FaceAPI->Face_Search(imgPath1, mn);
	printf("uid=%d\tsimilar=%f\n", mn.uid, mn.score);

	//搜索最相似的TopN数据，此示例N=6，相似度是降序
	MatchNode mn_arr[6];
	FaceAPI->Face_Search(4, mn_arr,6);
	for (int i =0; i< 6; i++)
	{
		printf("%d=>uid=%d\tsimilar=%f\n",i, mn_arr[i].uid, mn_arr[i].score);
	}
	//输出示例
	//0=>uid=4        similar=0.999990
	//1=>uid=1        similar=0.326334
	//2=>uid=3        similar=0.300490
	//3=>uid=2        similar=0.265565
	//4=>uid=6        similar=0.240211
	//5=>uid=5        similar=0.211910

	getchar();
	return 0;
}