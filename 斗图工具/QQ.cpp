#define _CRT_SECURE_NO_WARNINGS 1


#include <windows.h>
#include <stdio.h>
HWND FindTextBox(HWND hWnd)
{
	HWND hEdit = NULL;
	hEdit = FindWindowExW(hWnd, hEdit, L"Edit",0);
	//hEdit = FindWindowExW(hWnd, hEdit, L"վƱ��", 0);
	if (hEdit != NULL)
	{
		printf("վƱ��\n");
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
	HWND hWnd = FindWindowW(0, L"վƱ��");
	
	if (hWnd != 0)
	{
		printf("����ţ�%d\n",(int)hWnd);
		//SendMessageW(hWnd, WM_SETTEXT, 0, (LPARAM)L"xixi");
		//SendMessage(hWnd, WM_CLOSE, 0, 0);
		//printf("�رմ���\n");
		ShowWindow(hWnd, SW_SHOWNORMAL);  //�򿪴���
	}
	if (hWnd == 0) {
		puts("���Ҵ���ʧ�ܣ�");
		return 1;
	}

	printf("�����ɹ���!\n");
	HWND hEdit = NULL;
	hEdit = FindTextBox(hWnd);
	if (hEdit != NULL) {
		SendMessageW(hEdit, WM_SETTEXT, 0, (LPARAM)L"xixi");
		PostMessage(hEdit, WM_KEYDOWN, VK_RETURN, 0);
	}
	else {
		puts("��ȡ�༭��ʧ�ܣ�");
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
//		if (str.Find("����")>-1){//�ҵ�����������Begin
//			//��RichEdit
//			hWnd = FindWindowEx(pMainWnd->m_hWnd, NULL, "#32770", NULL);
//			pMainWnd = CWnd::FromHandle(hWnd);
//			hWnd = FindWindowEx(pMainWnd->m_hWnd, NULL, "AfxWnd42", NULL);
//			CWnd* pChildWnd = CWnd::FromHandle(hWnd);
//			int nLen = str.GetLength();
//			hNext = FindWindowEx(pChildWnd->m_hWnd, NULL, "RICHEDIT", NULL);
//			if (hNext){//�ҵ���Ϣ��д�ؼ�
//				CRichEditCtrl* pRich = (CRichEditCtrl*)(CWnd::FromHandle(hNext));
//				pRich->GetWindowText(str);
//				pRich->SetSel(nLen, nLen);
//				pRich->ReplaceSel("�ɶ������ѧУ �ƶ�");//���Ͻ�Ҫ���͵�����
//			}
//			else return;
//			//����Ϣ���Ͱ�ť
//			hWnd = FindWindowEx(pMainWnd->m_hWnd, NULL, NULL, NULL);
//			while (hWnd) {
//				pChildWnd = CWnd::FromHandle(hWnd);
//				pChildWnd->GetWindowText(str);
//				if (str.Find("����")>-1){
//					pChildWnd->SendMessage(BM_CLICK);//����
//					return;//���˳�
//				}
//				hWnd = FindWindowEx(pMainWnd->m_hWnd, hWnd, NULL, NULL);
//			}
//			return;
//		}//�ҵ�����������End
//		else pMainWnd = pMainWnd->GetWindow(GW_HWNDNEXT); //������
//	}//While
//}
//
//int main(void)
//{
//	/* ��ȡ�ļ����� */
//	char data[2000], data1[2000];
//	int j, i;
//	j = NULL;
//	puts("C����QQˢ���� By����õ����\n");
//	FILE *file = fopen("sendtext.txt", "r");
//	if (!file)
//	{
//		printf("�뽫Ҫ���͵���Ϣд�����ļ�Ŀ¼�µ� sendtext.txt �ļ���\n���û�У����½�һ��sendtext.txt�ļ���\n");
//		puts("ע�⣺���ܳ���2000���ַ���һ�������ֵ���2���ַ��������пո�");
//		system("pause");
//		return 0;
//	}
//	else if (!feof(file))
//	{
//		/* �����ļ����� */
//		fscanf(file, "%s", data);
//		//�滻ԭ���ļ���������  
//		if (OpenClipboard(NULL))//�򿪼�����  
//		{
//			if (IsClipboardFormatAvailable(CF_TEXT))
//			{
//				HANDLE hClip;
//				char *pBuf;
//				EmptyClipboard();//��ռ�����  
//				hClip = GlobalAlloc(GMEM_MOVEABLE, strlen(data) + 1);
//				pBuf = (char *)GlobalLock(hClip);
//				strcpy(pBuf, data);
//				GlobalUnlock(hClip);//����  
//				SetClipboardData(CF_TEXT, pBuf);//д���µļ���������  
//				CloseClipboard();
//				strcpy(data1, data);
//			}
//			else
//				CloseClipboard();//�رռ�����  
//		}
//	}
//	fclose(file);//�ر��ļ�  
//	printf("���ʹ�����");
//	scanf("%d", &j);
//	puts("ˢ����ʼ��");
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
//	printf("ˢ����ϣ���Ҫˢ %d �� һ��ˢ�� %d �Σ�\n", i, j);
//	keybd_event(VK_CONTROL, 0, 2, 0);
//	keybd_event(VK_v, 0, 2, 0);
//	keybd_event(VK_RETURN, 0, 2, 0);
//	system("pause");
//	return 0;
//}