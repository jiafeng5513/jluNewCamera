
// JluNewCameraDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "JluNewCamera.h"
#include "JluNewCameraDlg.h"
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CJluNewCameraDlg 对话框




CJluNewCameraDlg::CJluNewCameraDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJluNewCameraDlg::IDD, pParent)
	, m_nImageWidth(0)
	, m_nImageHeight(0)
	, m_nImageChannels(0)
	, m_ProcMethod(0)
	, m_ObjectWidth(0)
	, m_ObjectHeight(0)
	, m_ObjectDistance(0)
	, m_ObjectDisparity(0)
	, m_nCornerSize_X(0)
	, m_nCornerSize_Y(0)
	, m_nSquareSize(0)
	, m_nBoards(0)
	, m_nID_RAD(0)
	, m_nMinDisp(0)
	, m_nMaxDisp(0)
	, m_nSADWinSiz(0)
	, m_nTextThres(0)
	, m_nDisp12MaxDiff(-1)
	, m_nPreFiltCap(0)
	, m_nUniqRatio(0)
	, m_nSpeckRange(0)
	, m_nSpeckWinSiz(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CJluNewCameraDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDV_MinMaxInt(pDX, m_nCornerSize_X, 0, 50);
	DDV_MinMaxInt(pDX, m_nCornerSize_Y, 0, 50);
	DDV_MinMaxInt(pDX, m_nBoards, 0, 100);
	DDV_MinMaxInt(pDX, m_nMinDisp, -64, 16);
	DDV_MinMaxInt(pDX, m_nMaxDisp, 0, 240);
	DDV_MinMaxInt(pDX, m_nTextThres, 0, 50);
	DDV_MinMaxInt(pDX, m_nDisp12MaxDiff, -1, 16);
	DDV_MinMaxInt(pDX, m_nPreFiltCap, 0, 100);
	DDV_MinMaxInt(pDX, m_nUniqRatio, 0, 50);
	DDV_MinMaxInt(pDX, m_nSpeckRange, 0, 64);
	DDV_MinMaxInt(pDX, m_nSpeckWinSiz, 0, 200);
	DDX_Text(pDX, IDC_EDIT_speckWinSiz, m_nSpeckWinSiz);
	DDX_Text(pDX, IDC_EDIT_speckRange, m_nSpeckRange);
	DDX_Text(pDX, IDC_EDIT_uniqRatio, m_nUniqRatio);
	DDX_Text(pDX, IDC_EDIT_preFiltCap, m_nPreFiltCap);
	DDX_Text(pDX, IDC_e7ObjDist, m_ObjectDistance);
	DDX_Text(pDX, IDC_BoardWidth, m_nCornerSize_X);
	DDX_Text(pDX, IDC_BoardHeight, m_nCornerSize_Y);
	DDX_Text(pDX, IDC_SquareSize, m_nSquareSize);
	DDX_Text(pDX, IDC_EDIT_minDisp, m_nMinDisp);
	DDX_Text(pDX, IDC_nBoards, m_nBoards);
	DDX_Text(pDX, IDC_EDIT_maxDisp, m_nMaxDisp);
	DDX_Text(pDX, IDC_EDIT_SADWinSiz, m_nSADWinSiz);
	DDX_Text(pDX, IDC_EDIT_textThres, m_nTextThres);
	DDX_Text(pDX, IDC_EDIT_disp12MaxDiff, m_nDisp12MaxDiff);
}

BEGIN_MESSAGE_MAP(CJluNewCameraDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BN_DefaultCamCalibParam, &CJluNewCameraDlg::OnBnClickedBnDefaultcamcalibparam)
	ON_BN_CLICKED(IDC_BNDETECTAG, &CJluNewCameraDlg::OnBnClickedBndetectag)
	ON_BN_CLICKED(IDC_BN2StereoCalib, &CJluNewCameraDlg::OnBnClickedBn2stereocalib)
	ON_BN_CLICKED(IDC_BN_StereoDefParam, &CJluNewCameraDlg::OnBnClickedBnStereodefparam)
	ON_BN_CLICKED(IDC_BNGIVEDISP, &CJluNewCameraDlg::OnBnClickedBngivedisp)
	ON_BN_CLICKED(IDC_BN_CompDisp, &CJluNewCameraDlg::OnBnClickedBnCompdisp)
	ON_BN_CLICKED(IDC_RAD_BM, &CJluNewCameraDlg::OnBnClickedRadBm)
	ON_BN_CLICKED(IDC_RAD_SGBM, &CJluNewCameraDlg::OnBnClickedRadSgbm)
	ON_BN_CLICKED(IDC_BN_MOUSEON, &CJluNewCameraDlg::OnBnClickedBnMouseon)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_FACEDETECT, &CJluNewCameraDlg::OnBnClickedFacedetect)
	ON_BN_CLICKED(IDC_ONLYDISP, &CJluNewCameraDlg::OnBnClickedOnlydisp)
	ON_BN_CLICKED(IDC_SGBMTEST, &CJluNewCameraDlg::OnBnClickedSgbmtest)
END_MESSAGE_MAP()


// CJluNewCameraDlg 消息处理程序

BOOL CJluNewCameraDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CheckRadioButton(IDC_RAD_BOUGUET, IDC_RAD_BOUGUET, IDC_RAD_BOUGUET);				// 默认使用BOUGUET方法双目校正
	CheckRadioButton(IDC_RAD_BM, IDC_RAD_SGBM, IDC_RAD_BM);	// 默认使用 BM 算法计算视差	
	CheckRadioButton(IDC_RAD_CalibFromImg, IDC_RAD_CalibFromImg, IDC_RAD_CalibFromImg);
	m_nMaxDisp = 0;
	m_nSADWinSiz =0;
	m_nPreFiltCap =0;
	m_nSpeckRange = 0;
	UpdateData( FALSE );

	// 初始化图像显示控件的图像
	CRect rect;
	GetDlgItem(IDC_PicLfCam) ->GetClientRect( &rect );
	m_lfImage = Mat::zeros(rect.Height(), rect.Width(), CV_8UC3);
	GetDlgItem(IDC_PicRiCam) ->GetClientRect( &rect );
	m_riImage = Mat::zeros(rect.Height(), rect.Width(), CV_8UC3);
	GetDlgItem(IDC_PicSynImg) ->GetClientRect( &rect );
	m_disparity = Mat::zeros(rect.Height(), rect.Width(), CV_8UC3);
	//使一些控件处于无效状态
	GetDlgItem(IDC_BN_CompDisp)->EnableWindow(FALSE);
	GetDlgItem(IDC_BN_MOUSEON)->EnableWindow(FALSE);
	GetDlgItem(IDC_BN2StereoCalib)->EnableWindow(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CJluNewCameraDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CJluNewCameraDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		CDialog::UpdateWindow();				// 更新windows窗口，如果无这步调用，图片显示还会出现问题
		if (!m_lfImage.empty()||m_riImage.empty()||!m_disparity.empty())
		{
			F_ShowImage( m_lfImage, m_lfImage, IDC_PicLfCam );		// 重绘图片函数
			F_ShowImage( m_riImage, m_riImage, IDC_PicRiCam );		// 重绘图片函数
			F_ShowImage( m_disparity, m_disparity, IDC_PicSynImg );	// 重绘图片函数
		}
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CJluNewCameraDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int flag;
/*----------------------------
 * 功能 : 显示图像
 *		 将要绘制的图像 src 复制到 des，然后绘制到控件号为 ID 的 Picture 控件
 *----------------------------
 * 函数 : CStereoVisionDlg::F_ShowImage
 * 访问 : private 
 * 返回 : void
 *
 * 参数 : src	[in]	待显示图像
 * 参数 : des	[in]	窗口图像
 * 参数 : ID		[in]	图像窗口控件ID
 */
void CJluNewCameraDlg::F_ShowImage(Mat& src, Mat& des, UINT ID)
{
	if (src.empty())
	{
		return;
	}
	// 计算将图片缩放到 Image 区域所需的比例因子
	double wRatio = des.cols / (double)src.cols;
	double hRatio = des.rows / (double)src.rows;
	double srcWH = src.cols / (double)src.rows;
	double desWH = des.cols / (double)des.rows;
	double scale = srcWH > desWH ? wRatio : hRatio;

	// 缩放后图片的宽和高
	int nw = (int)( src.cols * scale );
	int nh = (int)( src.rows * scale );

	// 为了将缩放后的图片存入 des 的正中部位，需计算图片在 des 左上角的期望坐标值
	int tlx = (int)((des.cols - nw) / 2);
	int tly = (int)((des.rows - nh) / 2);

	// 设置 des 的 ROI 区域，用来存入图片 img
	Mat desRoi = des(Rect(tlx, tly, nw, nh));

	// 如果src是单通道图像，则转换为三通道图像
	if (src.channels() == 1)
	{
		Mat src_c;
		cvtColor(src, src_c, CV_GRAY2BGR);
		// 对图片 src_t 进行缩放，并存入到 des 中
		resize(src_c, desRoi, desRoi.size());
	}
	else
	{
		// 对图片 src 进行缩放，并存入到 des 中
		resize( src, desRoi, desRoi.size() );
	}

	CDC* pDC = GetDlgItem( ID ) ->GetDC();		// 获得显示控件的 DC
	HDC hDC = pDC ->GetSafeHdc();				// 获取 HDC(设备句柄) 来进行绘图操作
	CRect rect;
	GetDlgItem(ID) ->GetClientRect( &rect );	// 获取控件尺寸位置
	CvvImage cimg;
	IplImage cpy = des;
	cimg.CopyOf( &cpy );						// 复制图片
	cimg.DrawToHDC( hDC, &rect );				// 将图片绘制到显示控件的指定区域内
	ReleaseDC( pDC );
}

/*----------------------------
 * 功能 : 弹出打开文件对话框，选择单个或多个文件
 *----------------------------
 * 函数 : CStereoVisionDlg::DoSelectFiles
 * 访问 : private 
 * 返回 : selectedFiles	选择的文件的路径序列
 *
 * 参数 : lpszDefExt			[in]	文件默认格式
 * 参数 : dwFlags			[in]	对话框选项
 * 参数 : lpszFilter			[in]	文件格式过滤条件
 * 参数 : lpstrTitle			[in]	对话框标题
 * 参数 : lpstrInitialDir	[in]	对话框的初始路径
 */
vector<CStringA> CJluNewCameraDlg::DoSelectFiles(
	LPCTSTR	lpszDefExt,
	DWORD	dwFlags,
	LPCTSTR	lpszFilter,
	LPCWSTR	lpstrTitle,
	LPCWSTR	lpstrInitialDir )
{
	vector<CStringA> selectedFiles;
	POSITION filePosition;
	DWORD MAXFILE = 4000;  
	TCHAR* pc = new TCHAR[MAXFILE];  

	CFileDialog dlg( TRUE, lpszDefExt, NULL, dwFlags, lpszFilter, NULL );	
	
	dlg.m_ofn.nMaxFile = MAXFILE; 
	dlg.m_ofn.lpstrFile = pc;   
	dlg.m_ofn.lpstrFile[0] = NULL; 
	dlg.m_ofn.lpstrTitle = lpstrTitle;
	dlg.m_ofn.lpstrInitialDir = lpstrInitialDir;

	if( dlg.DoModal() == IDOK )
	{
		filePosition = dlg.GetStartPosition();
		while(filePosition != NULL)   
		{   
			CStringA path;
			path = dlg.GetNextPathName(filePosition);
			selectedFiles.push_back( path );  
		}  
	}

	delete []pc;
	return selectedFiles;
}

void CJluNewCameraDlg::OnBnClickedBnDefaultcamcalibparam()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nCornerSize_X = 9;
	m_nCornerSize_Y = 6;
	m_nBoards = 20;
	m_nSquareSize = 20.0f;
	UpdateData(FALSE);
	CheckRadioButton(IDC_RAD_CalibFromImg, IDC_RAD_CalibFromImg, IDC_RAD_CalibFromImg);
	return;

}

/************************
为分开角点检测和标定而定义的全局变量
***************************/

calib::CornerDatas cornerDatas;
calib::StereoParams stereoParams;
calib::RemapMatrixs remapMatrixs;
CJluNewCameraDlg::OptionCameraCalib optCalib;
void CJluNewCameraDlg::OnBnClickedBndetectag()
{
	// TODO: 在此添加控件通知处理程序代码
	/*进行初始化
	*/
	GetDlgItem(IDC_BN2StereoCalib)->EnableWindow(TRUE);
	const char* cornerFile = "CornerData.yml";
	int nFoundBoard = 0,nFrame=0;
	vector<CStringA> img0Files, img1Files;
	const char* img0_file = NULL, *img1_file = NULL;
	cv::Mat frame0, frame1, img0, img1;
	cv::Size imageSize;
	GetDlgItem(IDC_BN2StereoCalib)->EnableWindow(FALSE);
	UpdateData(TRUE);
	
	try
	{
		
		optCalib.cornerSize.width = m_nCornerSize_X; 	// 棋盘角点数 (nx, ny)
	    optCalib.cornerSize.height = m_nCornerSize_Y;
	    optCalib.numberBoards = m_nBoards;				// 检测棋盘次数
	    optCalib.squareSize = m_nSquareSize;
		m_nID_RAD = GetCheckedRadioButton(IDC_RAD_CalibFromImg, IDC_RAD_CalibFromImg);
	
		optCalib.readLocalImage = m_nID_RAD == IDC_RAD_CalibFromImg;
		if(optCalib.readLocalImage)		// 若从本地图片读入，则跳帧数减少为 5 帧
			optCalib.numberFrameSkip = 5;
		if(optCalib.readLocalImage)
		{
				
			img0Files = DoSelectFiles(
				_T("*.bmp"), 
				OFN_ENABLESIZING   |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
				_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
				_T("选择左视图文件"),
				_T("Imgs\\Left"));
				img1Files = DoSelectFiles(
					_T("*.bmp"), 
					OFN_ENABLESIZING   |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
					_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
					_T("选择右视图文件"),
					_T("Imgs\\Right"));//在这选完之后，以后创建的文件，只要没有指定路径，此就为它的默认路径。。。。
				
				if( img0Files.empty() )	// 判断是否获得图片
				{
					LPCTSTR errMsg = _T("没有选择到有效的图像文件，请重新选择!");
					throw errMsg;
				}
				
				img0_file = img0Files[ 0 ];
				img0 = cvLoadImage(img0_file);
				if(img0.rows>1000)
				{
					cv::resize(img0,img0,Size(img0.cols/6,img0.rows/6));
				//	cv::resize(img1,img1,Size(img1.cols/6,img1.rows/6));
						//AfxMessageBox(_T("lslslsl"));
				}
				imageSize = img0.size();

				if (false == img1Files.empty())
				{
					optCalib.numberBoards = MIN(optCalib.numberBoards, MIN(img0Files.size(), img1Files.size()));
					optCalib.doStereoCalib = true;
				}
				else
				{
					optCalib.doStereoCalib = false;
					optCalib.numberBoards = MIN(optCalib.numberBoards, img0Files.size());
				}
				m_stereoCalibrator.initCornerData(optCalib.numberBoards, imageSize, optCalib.cornerSize, optCalib.squareSize, cornerDatas);
			
				// 开始检测角点
				//MSG msg;
				while(nFoundBoard < optCalib.numberBoards)
				{

					// 载入图像
					if(optCalib.readLocalImage)	// 从本地图片
					{
						img0_file = img0Files[ nFoundBoard ];
						frame0 = cvLoadImage(img0_file);
					// 复制图像
						img0 = frame0.clone();
						if(img0.rows>1000)
						{
							cv::resize(img0,img0,Size(img0.cols/6,img0.rows/6));
						//	cv::resize(img1,img1,Size(img1.cols/6,img1.rows/6));
						//AfxMessageBox(_T("lslslsl"));
						}
						if (optCalib.doStereoCalib)
						{
							img1_file = img1Files[ nFoundBoard ];
							frame1 = cvLoadImage(img1_file);
							img1 = frame1.clone();
							if(img1.rows>1000)
							{
								//cv::resize(img0,img0,Size(img0.cols/6,img0.rows/6));
								cv::resize(img1,img1,Size(img1.cols/6,img1.rows/6));
						//AfxMessageBox(_T("lslslsl"));
							}
						}
					} 
		//			if (optCalib.doStereoCalib) img1 = frame1.clone();
					if(img0.rows>1000)
					{
						cv::resize(img0,img0,Size(img0.cols/6,img0.rows/6));
						cv::resize(img1,img1,Size(img1.cols/6,img1.rows/6));
						//AfxMessageBox(_T("lslslsl"));
					}
					// 检测角点
					if ( m_stereoCalibrator.detectCorners(img0, img1, cornerDatas, nFoundBoard) )
					{
						//if (nFrame++ > optCalib.numberFrameSkip)
						//{
							//保存视图
						/*	if (optCalib.readLocalImage == false)
							{
								CStringA imgName( m_workDir );
								imgName.AppendFormat("Images\\left%03d.jpg",nFoundBoard);
								string imgname = imgName.GetBuffer(0);
								imwrite(imgname, frame0);

								if (optCalib.doStereoCalib) 
								{
									imgName = m_workDir;
									imgName.AppendFormat("Images\\right%03d.jpg",nFoundBoard);
									imgname = imgName.GetBuffer(0);
									imwrite(imgname, frame1);
								}
							}*/

							nFoundBoard++; 
							nFrame = 0;
						//}

						if (nFoundBoard > 0 && nFrame < 5)
						{
							//使图像反色，表明同时找到完整的棋盘角点
							bitwise_not(img0, img0);
							if (optCalib.doStereoCalib) bitwise_not(img1, img1);
						}
					} // --End "if ( m_stereoCalibrator.detectCorners )"

					// 显示检测到的角点
					F_ShowImage( img0, m_lfImage, IDC_PicLfCam );
					F_ShowImage( img1, m_riImage, IDC_PicRiCam ); 
				} // --End "while(nFoundBoard < optCalib.numberBoards) "
			
				if (nFoundBoard < 4)
				{
				//	LPCTSTR errMsg = _T("检测成功的棋盘图像数小于4个，退出双目标定!");
				//	throw errMsg;
					CString str;
				//	str.Format("%d",nFoundBoard);
					str.Format(_T("%d"),nFoundBoard);
					AfxMessageBox(str);

				}
				else if (nFoundBoard != optCalib.numberBoards)
				{
					optCalib.numberBoards = nFoundBoard;
					m_stereoCalibrator.resizeCornerData(optCalib.numberBoards, cornerDatas);
				}
			
				// 保存角点坐标数据
				m_stereoCalibrator.saveCornerData(cornerFile, cornerDatas);
				GetDlgItem(IDC_BN2StereoCalib)->EnableWindow(TRUE);
				AfxMessageBox(_T("棋盘角点检测结束"));
			// 已获取角点坐标数据
		} 
		}
	catch (LPCTSTR errMsg)
	{
		AfxMessageBox(errMsg);
	}
	catch (cv::Exception& e)
	{
		char err[2048];
		sprintf_s(err, "发生错误: %s", e.what());
		CStringW errInfo;
		errInfo = err;
		AfxMessageBox(errInfo);
	}
	catch (...)
	{
		AfxMessageBox(_T("发生未知错误！"));
	}
}


void CJluNewCameraDlg::OnBnClickedBn2stereocalib()
{
	// TODO: 在此添加控件通知处理程序代码
//	stereoParams.cameraParams1.flags = optCalib.flagCameraCalib;
//	stereoParams.cameraParams2.flags = optCalib.flagCameraCalib;
	stereoParams.flags = 0;//CV_CALIB_FIX_PRINCIPAL_POINT|CV_CALIB_USE_INTRINSIC_GUESS|CV_CALIB_FIX_ASPECT_RATIO|CV_CALIB_SAME_FOCAL_LENGTH
	//bool needCalibSingleCamera = TRUE;
	bool needCalibSingleCamera = FALSE;
	stereoParams.alpha=-1;
	m_stereoCalibrator.calibrateStereoCamera(cornerDatas, stereoParams, needCalibSingleCamera);

	// 计算标定误差
	double avgErr = 0;
	m_stereoCalibrator.getStereoCalibrateError(cornerDatas, stereoParams, avgErr);
	char info[50];
	sprintf_s( info, "标定误差 = %7.4g", avgErr );
	CString ss;
	ss = info;
	AfxMessageBox(ss);
	m_nID_RAD = GetCheckedRadioButton(IDC_RAD_BOUGUET, IDC_RAD_BOUGUET);
	optCalib.rectifyMethod = m_nID_RAD == IDC_RAD_BOUGUET ? calib::RECTIFY_BOUGUET : calib::RECTIFY_HARTLEY;		
			// 执行双目校正
	m_stereoCalibrator.rectifyStereoCamera(cornerDatas, stereoParams, remapMatrixs, optCalib.rectifyMethod);
	//得到重投影矩阵和校正映射矩阵
	AfxMessageBox(_T("已完成双目校正"));
			
	// 保存摄像头定标参数	
	m_stereoCalibrator.saveCalibrationDatas("calib_paras.xml"/*待改为由本地设置文件确定*/, optCalib.rectifyMethod, cornerDatas, stereoParams, remapMatrixs);
	AfxMessageBox(_T("已保存定标参数"));
}


void CJluNewCameraDlg::OnBnClickedBnStereodefparam()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nID_RAD = GetCheckedRadioButton(IDC_RAD_BM, IDC_RAD_SGBM);
	CheckRadioButton(IDC_RAD_DispFromImg, IDC_RAD_DispFromImg, IDC_RAD_DispFromImg);
	if (m_nID_RAD == IDC_RAD_BM)
	{
		m_nMinDisp = 0;	
		m_nMaxDisp = 144;
		m_nSADWinSiz = 53;
		m_nTextThres = 10;
		m_nDisp12MaxDiff = 1;
		m_nPreFiltCap = 31;
		m_nUniqRatio = 25;
		m_nSpeckRange = 32;
		m_nSpeckWinSiz = 100;
		UpdateData(FALSE);
	} 
	else if(m_nID_RAD == IDC_RAD_SGBM)
	{
		m_nMinDisp = 0;	
		m_nMaxDisp = 144;
		m_nSADWinSiz = 25;
		m_nDisp12MaxDiff = 1;
		m_nPreFiltCap = 63;
		m_nUniqRatio = 20;
		m_nSpeckRange = 32;
		m_nSpeckWinSiz = 100;
//		m_nUniqRatio = 10;
//		sgbm.P1 = 8*cn*sgbm.SADWindowSize*sgbm.SADWindowSize;
//       sgbm.P2 = 32*cn*sgbm.SADWindowSize*sgbm.SADWindowSize;
//		m_pCheck = (CButton*)GetDlgItem(IDC_CHK_fullDP);
//		m_pCheck->SetCheck(0);
		UpdateData(FALSE);
	}
	
}
void CJluNewCameraDlg::FixDisp(Mat_<float> & disp,int numofdisp)
{
	Mat_<float> disp1;
	float lastPixel = 10;
	int minDisparity = 23;
//	disp.at<float>(0,144) = lastPixel;
	for (int i = 0; i < disp.rows; i++)
	{
		for (int j = numofdisp; j < disp.cols; j++)
		{
			if (disp(i,j) <= minDisparity) disp(i,j) = lastPixel;
			else lastPixel = disp(i,j);
		}
	}
	int an = 4;
	copyMakeBorder(disp, disp1, an,an,an,an, BORDER_REPLICATE);
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(an*2+1, an*2+1));
	morphologyEx(disp1, disp1, CV_MOP_OPEN, element);
	morphologyEx(disp1, disp1, CV_MOP_CLOSE, element);
	disp = disp1(Range(an, disp.rows-an), Range(an, disp.cols-an)).clone();
}
cv::Mat img1, img2, img1p, img2p, disp8u, pointCloud;
cv::Mat disp;
StereoMatch m_stereoMatcher;

void CJluNewCameraDlg::OnBnClickedBngivedisp()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_BN_CompDisp)->EnableWindow(TRUE);
	CJluNewCameraDlg::OptionCameraCalib opt;
//	m_nID_RAD = GetCheckedRadioButton(IDC_RAD_BM, IDC_RAD_BM);
//	opt.stereoMethod = m_nID_RAD == IDC_RAD_BM ? STEREO_BM :
//		m_nID_RAD == IDC_RAD_SGBM ? STEREO_SGBM : STEREO_BM;
//	m_nID_RAD=STEREO_BM;
	m_nID_RAD = GetCheckedRadioButton(IDC_RAD_DispFromImg, IDC_RAD_DispFromImg);
	opt.readLocalImage = m_nID_RAD == IDC_RAD_DispFromImg;
	CStringA xmlPath;			// 定标结果数据文件
	vector<CStringA> imgFiles1; //左右视图文件路径序列
	vector<CStringA> imgFiles2;	
	OptionStereoMatch optMatch;
	int i = 0, j = 0;
	const char* img1_filename = NULL;
	const char* img2_filename = NULL;
	const char* xml_filename = NULL;

//	cv::Mat img1, img2, img1p, img2p, disp, disp8u, pointCloud;
	LPCTSTR errMsg;
	try
	{
		if (opt.readLocalImage)
		{
			// 选择左视图
			imgFiles1 = DoSelectFiles(
				_T("*.bmp"), 
				OFN_ENABLESIZING |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
				_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
				_T("选择左视图图像"),
				m_workDir
				);
			// 选择右视图
			imgFiles2 = DoSelectFiles(
				_T("*.bmp"), 
				OFN_ENABLESIZING |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
				_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
				_T("选择右视图图像"),
				m_workDir
				);

			if( imgFiles1.empty() || imgFiles2.empty() )	
			{
				errMsg = _T("没有选中有效的图像文件!");
				throw errMsg;
			}

			img1_filename = imgFiles1[0];
			img2_filename = imgFiles2[0];
			img1 = imread(img1_filename);
			img2 = imread(img2_filename);
			if(img1.rows>1000)
			{
				cv::resize(img1,img1,Size(img1.cols/6,img1.rows/6));
				cv::resize(img2,img2,Size(img2.cols/6,img2.rows/6));
			//AfxMessageBox(_T("lslslsl"));
			}
		} 
	}
	catch (LPCTSTR ErrMsg)
	{
		AfxMessageBox(ErrMsg);
		return;
	}
	catch (cv::Exception& e)
	{
		char err[2048];
		sprintf_s(err, "发生错误: %s", e.what());
		CStringW errInfo;
		errInfo = err;
		AfxMessageBox(errInfo);
		return;
	}
	catch (...)
	{
		AfxMessageBox(_T("发生未知错误！"));
		return;
	}
	try
	{
		vector<CStringA> xmlFiles;
		xmlFiles = DoSelectFiles(
			_T("*.xml"), 
			OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
			_T("XML/YML file (*.xml; *.yml) |*.xml; *.yml | All Files (*.*) |*.*||"), 
			_T("选择摄像头定标参数文件"),
			m_workDir
			);
		if( xmlFiles.empty() )	
		{
			errMsg = _T("没有选中有效的摄像头定标参数文件!");			
			throw errMsg;
		}
		xmlPath = xmlFiles[0];			// 获取xml文件路径
		xml_filename = xmlPath;
	//	StereoMatch m_stereoMatcher;
		// 读入摄像头定标参数
		switch (m_stereoMatcher.init(img1.cols, img1.rows, xml_filename))
		{
		case 0:
		case -99:
		errMsg = _T("读取摄像头定标参数文件失败，请重新选择!");			
		throw errMsg;
		case -1:
				errMsg = _T("定标参数的图像尺寸与当前配置的图像尺寸不一致，请重新选择!");			
				throw errMsg;
				break;
		}
	}
	catch (LPCTSTR ErrMsg)
	{
		AfxMessageBox(ErrMsg);
		return;
	}
	catch (cv::Exception& e)
	{
		char err[2048];
		sprintf_s(err, "发生错误: %s", e.what());
		CStringW errInfo;
		errInfo = err;
		AfxMessageBox(errInfo);
		return;
	}
	catch (...)
	{
		AfxMessageBox(_T("发生未知错误！"));
		return;
	}
	m_stereoMatcher.m_BM.state->disp12MaxDiff = m_nDisp12MaxDiff;
	m_stereoMatcher.m_SGBM.disp12MaxDiff = m_nDisp12MaxDiff;
	int frameCount = 0;	//图像计数
	m_nID_RAD = GetCheckedRadioButton(IDC_RAD_BM, IDC_RAD_SGBM);
	optMatch.stereoMethod = m_nID_RAD == IDC_RAD_BM ? STEREO_BM :
		m_nID_RAD == IDC_RAD_SGBM ? STEREO_SGBM : STEREO_BM;
	while(true)
	{
		if (frameCount >= MIN(imgFiles1.size(), imgFiles2.size()))
					break;
		img1_filename = imgFiles1[frameCount];
		img2_filename = imgFiles2[frameCount];
		img1 = imread(img1_filename, 1);
		img2 = imread(img2_filename, 1);
		if(img1.rows>1000)
		{
			cv::resize(img1,img1,Size(img1.cols/6,img1.rows/6));
			cv::resize(img2,img2,Size(img2.cols/6,img2.rows/6));
			//AfxMessageBox(_T("lslslsl"));
		}
		if(img1.empty() || img2.empty()) break;
		frameCount++;
		//进行update_state_BM
		if (optMatch.stereoMethod == STEREO_BM)
		{
			UpdateData(TRUE);
			m_stereoMatcher.m_BM.state->preFilterCap = m_nPreFiltCap;
			m_stereoMatcher.m_BM.state->SADWindowSize = m_nSADWinSiz;
			m_stereoMatcher.m_BM.state->minDisparity = m_nMinDisp;
			m_stereoMatcher.m_BM.state->numberOfDisparities = m_nMaxDisp;
			m_stereoMatcher.m_BM.state->textureThreshold = m_nTextThres;
			m_stereoMatcher.m_BM.state->uniquenessRatio = m_nUniqRatio;
			m_stereoMatcher.m_BM.state->speckleWindowSize = m_nSpeckWinSiz;
			m_stereoMatcher.m_BM.state->speckleRange = m_nSpeckRange;
		//	m_stereoMatcher.m_BM.state->preFilterSize=41;
			m_stereoMatcher.bmMatch(img1, img2, disp, img1p, img2p);//BM算法
		}
		else if (optMatch.stereoMethod == STEREO_SGBM)
		{
//			DoUpdateStateSGBM(img1.channels());
			int imgChannels=img1.channels();
			UpdateData(TRUE);
			m_stereoMatcher.m_SGBM.preFilterCap = m_nPreFiltCap;
			m_stereoMatcher.m_SGBM.SADWindowSize = m_nSADWinSiz;
			m_stereoMatcher.m_SGBM.P1 =  48 * imgChannels * m_nSADWinSiz * m_nSADWinSiz;
			m_stereoMatcher.m_SGBM.P2 = 48 * imgChannels * m_nSADWinSiz * m_nSADWinSiz;
			m_stereoMatcher.m_SGBM.minDisparity = m_nMinDisp;
			m_stereoMatcher.m_SGBM.numberOfDisparities = m_nMaxDisp;
			m_stereoMatcher.m_SGBM.uniquenessRatio = m_nUniqRatio;
			m_stereoMatcher.m_SGBM.speckleWindowSize = m_nSpeckWinSiz;
			m_stereoMatcher.m_SGBM.speckleRange = m_nSpeckRange;
			m_stereoMatcher.m_SGBM.fullDP = true;
			m_stereoMatcher.sgbmMatch(img1, img2, disp, img1p, img2p);
			
		}
		for( j = 0; j < img1p.rows; j += 32 )		
		{
			line( img1p, cvPoint(0,j),	cvPoint(img1p.cols,j), CV_RGB(0,255,0)); 
			line( img2p, cvPoint(0,j),	cvPoint(img2p.cols,j), CV_RGB(0,255,0)); 
		}
		//保存视差图像到本地文件夹
/*		std::string str="./";
		cv::imwrite(str+"disp1.jpg",disp);
		imshow("222llll",disp);
		///
		Mat_<float> disptemp;
		disp.convertTo(disptemp,CV_32FC1,1.0/16);
		imshow("llll",disptemp);
	//	FixDisp(disptemp,m_nMaxDisp);
		std::string str1="./";
		cv::imwrite(str1+"disp.jpg",disptemp);
		imshow("llll2",disptemp);*/
    	m_stereoMatcher.getDisparityImage(disp, disp8u, true);//得到伪彩
//		imshow("lslsl",disp8u);
		F_ShowImage( img1p, m_lfImage, IDC_PicLfCam );
		F_ShowImage( img2p, m_riImage, IDC_PicRiCam );
		F_ShowImage( disp8u, m_disparity, IDC_PicSynImg );
/*		NamedWindow("lslsls",CV_WINDOW_AUTOSIZE);
	    imshow("lslsls",disp8u);
	    waitKey(0);*/
	}
}


void CJluNewCameraDlg::OnBnClickedBnCompdisp()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_BN_MOUSEON)->EnableWindow(TRUE);
	m_stereoMatcher.getPointClouds(disp, pointCloud);//生成三维点云并进行Y轴反转
	vector<PointCloudAnalyzer::ObjectInfo> objectInfos;
	PointCloudAnalyzer pointCloudAnalyzer;
	pointCloudAnalyzer.detectNearObject(disp8u, pointCloud, objectInfos);////////
	pointCloudAnalyzer.showObjectInfo(objectInfos, img1p);
	m_ObjectDistance = objectInfos[0].distance; m_ObjectDistance = (int)(m_ObjectDistance * 10000) / 10000.;
	m_ObjectDistance=-1*m_ObjectDistance;
	UpdateData(FALSE);
	F_ShowImage( img1p, m_lfImage, IDC_PicLfCam );
	F_ShowImage( img2p, m_riImage, IDC_PicRiCam );
	F_ShowImage( disp8u, m_disparity, IDC_PicSynImg );
}

void CJluNewCameraDlg::DoClearParamsOfStereoMatch(void)
{
	m_nMinDisp = 0;	
	m_nMaxDisp = 0;
	m_nSADWinSiz = 0;
	m_nTextThres = 0;
	m_nDisp12MaxDiff = -1;
	m_nPreFiltCap = 0;
	m_nUniqRatio = 0;
	m_nSpeckRange = 0;
	m_nSpeckWinSiz = 0;
	UpdateData(FALSE);
	return;
}
void CJluNewCameraDlg::OnBnClickedRadBm()
{
	// TODO: 在此添加控件通知处理程序代码
	DoClearParamsOfStereoMatch();
	CheckRadioButton(IDC_RAD_BM, IDC_RAD_SGBM, IDC_RAD_BM);
	GetDlgItem(IDC_EDIT_disp12MaxDiff)->EnableWindow(FALSE);

}


void CJluNewCameraDlg::OnBnClickedRadSgbm()
{
	// TODO: 在此添加控件通知处理程序代码
	DoClearParamsOfStereoMatch();
	CheckRadioButton(IDC_RAD_BM, IDC_RAD_SGBM, IDC_RAD_SGBM);
}

void CJluNewCameraDlg::OnBnClickedBnMouseon()
{
	// TODO: 在此添加控件通知处理程序代码
	moupoint.x=5;
	moupoint.y=5;
	vector<cv::Mat> xyzSet;
	split(pointCloud, xyzSet);
	cv::Mat depth;
	xyzSet[2].copyTo(depth);
	cv::namedWindow("鼠标点击测距",1);
	flag=1;
	while(flag)
	{
		imshow("鼠标点击测距",disp8u);
		cv::setMouseCallback( "鼠标点击测距",On_Mouse, 0 );
	
		if(moupoint.x>20)
		{
			flag=1;
			m_ObjectDistance=depth.at<float>(moupoint);
		//	m_ObjectDistance=depth.ptr<float>(moupoint.x)[moupoint.y];
			m_ObjectDistance=-1*m_ObjectDistance;
			if(m_ObjectDistance>0)
			{
			    UpdateData(FALSE);
			}
		}
	
	//	cv::waitKey(15);
		if( waitKey(100) == 27 )
			break;
	}
	destroyWindow("鼠标点击测距");
}


void CJluNewCameraDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	AfxMessageBox(_T("errInfo"));
//	CDialogEx::OnLButtonDown(nFlags, point);
/*	if(flag==1)
	{
		moupoint.x=5;
		moupoint.y=5;
		vector<cv::Mat> xyzSet;
		split(pointCloud, xyzSet);
		cv::Mat depth;
		xyzSet[2].copyTo(depth);
		CRect rect;
	 //this->GetClientRect(&rect);
	   (this->GetDlgItem(IDC_PicSynImg))->GetWindowRect(&rect);
	   ScreenToClient(rect);
	   // CPoint p(rect.right,rect.bottom);
/*	   CRect rect;
       m_edit->GetWindowRect(&rect);   //取得控件的全屏坐标
       this->ScreenToClient(&rect);        //转成客户窗口坐标，this指向控件所在的窗口。
	   moupoint.x=point.x-rect.left+50;
	   moupoint.y=point.y-rect.top+50;
	   CString str;
     //str.Format("%d",nFoundBoard);
	   str.Format(_T("%d"),moupoint.y);
//	   AfxMessageBox(str);
	   if(moupoint.x>10&&moupoint.y>10)
		{
			m_ObjectDistance=depth.at<float>(moupoint);
		//	m_ObjectDistance=depth.ptr<float>(moupoint.x)[moupoint.y];
			m_ObjectDistance=-2*m_ObjectDistance;
			if(m_ObjectDistance>0)
			{
			    UpdateData(FALSE);
			}
		}
	}*/
}


void CJluNewCameraDlg::OnBnClickedFacedetect()
{
	// TODO: 在此添加控件通知处理程序代码
	//初始化
	vector<CStringA> imgfaceFiles1; //左右视图文件路径序列
	vector<CStringA> imgfaceFiles2;	
	const char* img1_filename = NULL;
	const char* img2_filename = NULL;
	Mat faceimg1,faceimg2;
//	LPCTSTR errMsg;
	imgfaceFiles1 = DoSelectFiles(
				_T("*.bmp"), 
				OFN_ENABLESIZING |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
				_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.pgm; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
				_T("选择左视图图像"),
				m_workDir
				);		// 选择右视图

	if( imgfaceFiles1.empty() )	
	{
		//errMsg = _T("没有选中有效的图像文件!");
		//throw errMsg;
		AfxMessageBox(_T("没有选中图像文件！"));
		return;
	}
	img1_filename=imgfaceFiles1[0];
//	img2_filename=imgfaceFiles2[0];
	faceimg1=imread(img1_filename);
//	faceimg2=imread(img2_filename);
	int width=faceimg1.cols;
	int height=faceimg1.rows;
	//进行人脸检测
	string fn_haar = "E:\\wanghao\\FaceRecognizer\\haarcascade_frontalface_alt2.xml";
	CascadeClassifier haar_cascade;
    haar_cascade.load(fn_haar);
//	resize(faceimg1,faceimg1,Size(width/4,height/4),1.0,1.0,INTER_CUBIC);
	Mat gray;
    cvtColor(faceimg1, gray, CV_BGR2GRAY);
        // Find the faces in the frame:
    vector< Rect_<int> > faces;
	Mat imgrect;
    haar_cascade.detectMultiScale(gray, faces,1.3,4,0|CV_HAAR_SCALE_IMAGE,Size(30, 30));	
	for(int i=0;i<faces.size();i++)
	{
	
		
	Rect face1=faces[i];
//	Size size(20,20);
//	Rect facetemp=
//	face1=Rect(face1.tl(),face1.br()*1.5);
//	face1=face1+face1.size();
	/*
	Rect temp=Rect(face1.tl().x*0.8,face1.tl().y*0.4,face1.width*1.6,face1.height*1.7);*/
	imgrect=faceimg1(face1);
	rectangle(faceimg1, face1, CV_RGB(0, 255,0), 1);
	
	}
	Size dsize=Size(92,112);
	resize(imgrect,imgrect,dsize);
	cv::cvtColor(imgrect,imgrect,CV_BGR2GRAY);
	imshow("lslsl",faceimg1);
	imshow("haha",imgrect);
	imwrite("../test.pgm",imgrect);

}


void CJluNewCameraDlg::OnBnClickedOnlydisp()
{
	// TODO: 在此添加控件通知处理程序代码
	vector<CStringA> imgFiles1; //左右视图文件路径序列
	vector<CStringA> imgFiles2;	
	//OptionStereoMatch optMatch;
	int i = 0, j = 0;
	const char* img1_filename = NULL;
	const char* img2_filename = NULL;
	const char* xml_filename = NULL;
	imgFiles1 = DoSelectFiles(
				_T("*.bmp"), 
				OFN_ENABLESIZING |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
				_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
				_T("选择左视图图像"),
				m_workDir
				);
			// 选择右视图
			imgFiles2 = DoSelectFiles(
				_T("*.bmp"), 
				OFN_ENABLESIZING |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
				_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
				_T("选择右视图图像"),
				m_workDir
				);

			if( imgFiles1.empty() || imgFiles2.empty() )	
			{
			//	errMsg = _T("没有选中有效的图像文件!");
			//	throw errMsg;
			}
			img1_filename = imgFiles1[0];
			img2_filename = imgFiles2[0];
			IplImage * cv_left_rectified;
            IplImage * cv_right_rectified;
             cv_left_rectified = cvLoadImage( img1_filename, CV_LOAD_IMAGE_GRAYSCALE);
             cv_right_rectified = cvLoadImage( img2_filename, CV_LOAD_IMAGE_GRAYSCALE);
             CvSize size = cvGetSize( cv_left_rectified );
			CvMat * disparity_left = cvCreateMat(size.height,size.width,CV_16S);
			CvMat * disparity_right = cvCreateMat(size.height,size.width,CV_16S);	
////		
			m_stereoMatcher.GcMatch(cv_left_rectified,cv_right_rectified,disparity_left,disparity_right);
		/////
			// CV_BGR2GRAY
}


void CJluNewCameraDlg::OnBnClickedSgbmtest()
{
	// TODO: 在此添加控件通知处理程序代码
	vector<CStringA> imgFiles1; //左右视图文件路径序列
	vector<CStringA> imgFiles2;	
	//OptionStereoMatch optMatch;
	int i = 0, j = 0;
	const char* img1_filename = NULL;
	const char* img2_filename = NULL;
	const char* xml_filename = NULL;
	imgFiles1 = DoSelectFiles(
				_T("*.bmp"), 
				OFN_ENABLESIZING |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
				_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
				_T("选择左视图图像"),
				m_workDir
				);
			// 选择右视图
			imgFiles2 = DoSelectFiles(
				_T("*.bmp"), 
				OFN_ENABLESIZING |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
				_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
				_T("选择右视图图像"),
				m_workDir
				);

			if( imgFiles1.empty() || imgFiles2.empty() )	
			{
			//	errMsg = _T("没有选中有效的图像文件!");
			//	throw errMsg;
			}
			img1_filename = imgFiles1[0];
			img2_filename = imgFiles2[0];
			img1 = imread(img1_filename, 1);
		//	imshow("lsls1",img1);
	     	img2 = imread(img2_filename, 1);
		//	imshow("lsls2",img2);
			cv::cvtColor(img1,img1,CV_BGR2GRAY);
			cv::cvtColor(img2,img2,CV_BGR2GRAY);
		    //if(img1.empty() || img2.empty()) break;
			int imgChannels=img1.channels();
			m_stereoMatcher.m_SGBM.preFilterCap = 63;
			m_stereoMatcher.m_SGBM.SADWindowSize = 9;
			m_stereoMatcher.m_SGBM.P1 =  8 * imgChannels * m_nSADWinSiz * m_nSADWinSiz;
			m_stereoMatcher.m_SGBM.P2 = 32 * imgChannels * m_nSADWinSiz * m_nSADWinSiz;
			m_stereoMatcher.m_SGBM.minDisparity = 0;
			m_stereoMatcher.m_SGBM.numberOfDisparities = 64;
			m_stereoMatcher.m_SGBM.uniquenessRatio = 10;
			m_stereoMatcher.m_SGBM.speckleWindowSize = 100;
			m_stereoMatcher.m_SGBM.speckleRange = 32;
			m_stereoMatcher.m_SGBM.disp12MaxDiff = 1;
			m_stereoMatcher.sgbmMatch(img1, img2, disp, img1p, img2p);
			imshow("lsls",disp);

}
