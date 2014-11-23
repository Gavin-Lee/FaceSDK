#include "stdafx.h"
#include <Windows.h>
#include "FaceSDK/ComFaceSDK.h"
#pragma comment(lib,"FaceSDK/ComFaceSDK.lib")
//compare 2 face photo's similarity
int _tmain(int argc, _TCHAR* argv[])
{
    CComFaceSDK* FaceAPI = new CComFaceSDK();
	char imgPath1[] = "1.jpg";
	char imgPath2[] = "2.jpg";
	float score = FaceAPI->Compare2Image(imgPath1,imgPath2);
	printf("similar=%f\n",score);
	getchar();
	return 0;
}
