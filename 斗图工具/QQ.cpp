#define _CRT_SECURE_NO_WARNINGS 1


#include <windows.h>
#include <stdio.h>
HWND FindTextBox(HWND hWnd)
{
	HWND hEdit = NULL;
	hEdit = FindWindowExW(hWnd, hEdit, L"Edit",0);
	//hEdit = FindWindowExW(hWnd, hEdit, L"站票絮", 0);
	if (hEdit != NULL)
	{
		printf("站票絮\n");
		return hEdit;
	}
		
	

	HWND hChild = NULL;
	for (;;) {
		hChild = FindWindowExW(hWnd, hChild, 0, 0);
		if (hChild == NULL)
			break;
		hEdit = FindTextBox(hChild);
		if (hEdit != NULL)
			break;
	}
	return hEdit;
}
int main()
{
	HWND hWnd = FindWindowW(0, L"站票絮");
	
	if (hWnd != 0)
	{
		printf("句柄号：%d\n",(int)hWnd);
		//SendMessageW(hWnd, WM_SETTEXT, 0, (LPARAM)L"xixi");
		//SendMessage(hWnd, WM_CLOSE, 0, 0);
		//printf("关闭窗口\n");
		ShowWindow(hWnd, SW_SHOWNORMAL);  //打开窗口
	}
	if (hWnd == 0) {
		puts("查找窗口失败！");
		return 1;
	}

	printf("搜索成功了!\n");
	HWND hEdit = NULL;
	hEdit = FindTextBox(hWnd);
	if (hEdit != NULL) {
		SendMessageW(hEdit, WM_SETTEXT, 0, (LPARAM)L"xixi");
		PostMessage(hEdit, WM_KEYDOWN, VK_RETURN, 0);
	}
	else {
		puts("获取编辑框失败！");
		return 1;
	}
	
	return 0;
}
//#include <stdio.h>  
//#include <string.h>  
//#include <stdlib.h>  
//#include <windows.h>  
//#define   VK_v  0x56  
//
//void CMySMSDlg::QQSendMessage()
//{
//	CString str;
//	CWnd* pMainWnd = AfxGetMainWnd()->GetWindow(GW_HWNDFIRST);
//	while (pMainWnd)
//	{
//		HWND hWnd, hNext;
//		hWnd = pMainWnd->m_hWnd;
//		pMainWnd->GetWindowText(str);
//		if (str.Find("聊天")>-1){//找到聊天主窗口Begin
//			//找RichEdit
//			hWnd = FindWindowEx(pMainWnd->m_hWnd, NULL, "#32770", NULL);
//			pMainWnd = CWnd::FromHandle(hWnd);
//			hWnd = FindWindowEx(pMainWnd->m_hWnd, NULL, "AfxWnd42", NULL);
//			CWnd* pChildWnd = CWnd::FromHandle(hWnd);
//			int nLen = str.GetLength();
//			hNext = FindWindowEx(pChildWnd->m_hWnd, NULL, "RICHEDIT", NULL);
//			if (hNext){//找到消息填写控件
//				CRichEditCtrl* pRich = (CRichEditCtrl*)(CWnd::FromHandle(hNext));
//				pRich->GetWindowText(str);
//				pRich->SetSel(nLen, nLen);
//				pRich->ReplaceSel("成都外国语学校 黄东");//填上将要发送的内容
//			}
//			else return;
//			//找消息发送按钮
//			hWnd = FindWindowEx(pMainWnd->m_hWnd, NULL, NULL, NULL);
//			while (hWnd) {
//				pChildWnd = CWnd::FromHandle(hWnd);
//				pChildWnd->GetWindowText(str);
//				if (str.Find("发送")>-1){
//					pChildWnd->SendMessage(BM_CLICK);//发送
//					return;//　退出
//				}
//				hWnd = FindWindowEx(pMainWnd->m_hWnd, hWnd, NULL, NULL);
//			}
//			return;
//		}//找到聊天主窗口End
//		else pMainWnd = pMainWnd->GetWindow(GW_HWNDNEXT); //继续找
//	}//While
//}
//
//int main(void)
//{
//	/* 读取文件内容 */
//	char data[2000], data1[2000];
//	int j, i;
//	j = NULL;
//	puts("C语言QQ刷屏器 By：紫玫冰心\n");
//	FILE *file = fopen("sendtext.txt", "r");
//	if (!file)
//	{
//		printf("请将要发送的信息写到该文件目录下的 sendtext.txt 文件中\n如果没有，请新建一个sendtext.txt文件！\n");
//		puts("注意：不能超过2000个字符，一个中文字等于2个字符，不能有空格！");
//		system("pause");
//		return 0;
//	}
//	else if (!feof(file))
//	{
//		/* 读入文件数据 */
//		fscanf(file, "%s", data);
//		//替换原来的剪辑板数据  
//		if (OpenClipboard(NULL))//打开剪辑板  
//		{
//			if (IsClipboardFormatAvailable(CF_TEXT))
//			{
//				HANDLE hClip;
//				char *pBuf;
//				EmptyClipboard();//清空剪辑板  
//				hClip = GlobalAlloc(GMEM_MOVEABLE, strlen(data) + 1);
//				pBuf = (char *)GlobalLock(hClip);
//				strcpy(pBuf, data);
//				GlobalUnlock(hClip);//解锁  
//				SetClipboardData(CF_TEXT, pBuf);//写入新的剪辑板数据  
//				CloseClipboard();
//				strcpy(data1, data);
//			}
//			else
//				CloseClipboard();//关闭剪辑板  
//		}
//	}
//	fclose(file);//关闭文件  
//	printf("发送次数：");
//	scanf("%d", &j);
//	puts("刷屏开始！");
//	for (i = 0; i<j; i++)
//	{
//		keybd_event(VK_CONTROL, 0, 0, 0);
//		keybd_event(VK_v, 0, 0, 0);
//		keybd_event(VK_CONTROL, 0, 2, 0);
//		keybd_event(VK_v, 0, 2, 0);
//		keybd_event(VK_RETURN, 0, 0, 0);
//		keybd_event(VK_RETURN, 0, 2, 0);
//		Sleep(100);
//	}
//	printf("刷屏完毕！需要刷 %d 次 一共刷了 %d 次！\n", i, j);
//	keybd_event(VK_CONTROL, 0, 2, 0);
//	keybd_event(VK_v, 0, 2, 0);
//	keybd_event(VK_RETURN, 0, 2, 0);
//	system("pause");
//	return 0;
//}