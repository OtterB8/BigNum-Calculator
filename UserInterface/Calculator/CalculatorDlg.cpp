
// CalculatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCalculatorDlg dialog



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
	, m_EntryVal(_T(""))
	, m_History(_T(""))
	, m_HexVal(_T(""))
	, m_DecVal(_T(""))
	, m_BinVal(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ENTRY_VALUE, m_EntryVal);
	DDX_Text(pDX, IDC_EDIT_HISTORY, m_History);
	DDX_Text(pDX, IDC_HEX_VALUE, m_HexVal);
	DDX_Text(pDX, IDC_DEC_VALUE, m_DecVal);
	DDX_Text(pDX, IDC_BIN_VALUE, m_BinVal);
	DDX_Control(pDX, IDC_BUTTON_DEC, m_Button_Dec);
	DDX_Control(pDX, IDC_BUTTON_A, m_Button_A);
	DDX_Control(pDX, IDC_BUTTON_B, m_Button_B);
	DDX_Control(pDX, IDC_BUTTON_C, m_Button_C);
	DDX_Control(pDX, IDC_BUTTON_D, m_Button_D);
	DDX_Control(pDX, IDC_BUTTON_E, m_Button_E);
	DDX_Control(pDX, IDC_BUTTON_F, m_Button_F);
	DDX_Control(pDX, IDC_BUTTON_DOT, m_Button_Dot);
	DDX_Control(pDX, IDC_BUTTON_HEX, m_Button_Hex);
	DDX_Control(pDX, IDC_BUTTON_BIN, m_Button_Bin);
	DDX_Control(pDX, IDC_BUTTON_2, m_Button_2);
	DDX_Control(pDX, IDC_BUTTON_3, m_Button_3);
	DDX_Control(pDX, IDC_BUTTON_4, m_Button_4);
	DDX_Control(pDX, IDC_BUTTON_5, m_Button_5);
	DDX_Control(pDX, IDC_BUTTON_6, m_Button_6);
	DDX_Control(pDX, IDC_BUTTON_7, m_Button_7);
	DDX_Control(pDX, IDC_BUTTON_8, m_Button_8);
	DDX_Control(pDX, IDC_BUTTON_9, m_Button_9);
	DDX_Control(pDX, IDC_BUTTON_SWITCH, m_Button_Switch);
	DDX_Control(pDX, IDC_BUTTON_Lsh, m_Button_Lsh);
	DDX_Control(pDX, IDC_BUTTON_Rsh, m_Button_Rsh);
	DDX_Control(pDX, IDC_BUTTON_Or, m_Button_Or);
	DDX_Control(pDX, IDC_BUTTON_Xor, m_Button_Xor);
	DDX_Control(pDX, IDC_BUTTON_Not, m_Button_Not);
	DDX_Control(pDX, IDC_BUTTON_And, m_Button_And);
	DDX_Control(pDX, IDC_BUTTON_RoL, m_Button_RoL);
	DDX_Control(pDX, IDC_BUTTON_RoR, m_Button_RoR);
	DDX_Control(pDX, IDC_BUTTON_0, m_Button_0);
	DDX_Control(pDX, IDC_BUTTON_1, m_Button_1);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_0, &CCalculatorDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_1, &CCalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, &CCalculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, &CCalculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_4, &CCalculatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_5, &CCalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, &CCalculatorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_7, &CCalculatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON_8, &CCalculatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, &CCalculatorDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON_A, &CCalculatorDlg::OnBnClickedButtonA)
	ON_BN_CLICKED(IDC_BUTTON_B, &CCalculatorDlg::OnBnClickedButtonB)
	ON_BN_CLICKED(IDC_BUTTON_C, &CCalculatorDlg::OnBnClickedButtonC)
	ON_BN_CLICKED(IDC_BUTTON_D, &CCalculatorDlg::OnBnClickedButtonD)
	ON_BN_CLICKED(IDC_BUTTON_E, &CCalculatorDlg::OnBnClickedButtonE)
	ON_BN_CLICKED(IDC_BUTTON_F, &CCalculatorDlg::OnBnClickedButtonF)
	ON_BN_CLICKED(IDC_BUTTON_Backspace, &CCalculatorDlg::OnBnClickedButtonBackspace)
	ON_BN_CLICKED(IDC_BUTTON_SIGN, &CCalculatorDlg::OnBnClickedButtonSign)
	ON_BN_CLICKED(IDC_BUTTON_DOT, &CCalculatorDlg::OnBnClickedButtonDot)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_HEX, &CCalculatorDlg::OnBnClickedButtonHex)
	ON_BN_CLICKED(IDC_BUTTON_DEC, &CCalculatorDlg::OnBnClickedButtonDec)
	ON_BN_CLICKED(IDC_BUTTON_BIN, &CCalculatorDlg::OnBnClickedButtonBin)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CCalculatorDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_CE, &CCalculatorDlg::OnBnClickedButtonCe)
	ON_BN_CLICKED(IDC_BUTTON_PLUS, &CCalculatorDlg::OnBnClickedButtonPlus)
	ON_BN_CLICKED(IDC_BUTTON_SUBTRACT, &CCalculatorDlg::OnBnClickedButtonSubtract)
	ON_BN_CLICKED(IDC_BUTTON_MULTIPLY, &CCalculatorDlg::OnBnClickedButtonMultiply)
	ON_BN_CLICKED(IDC_BUTTON_DIVIDE, &CCalculatorDlg::OnBnClickedButtonDivide)
	ON_BN_CLICKED(IDC_BUTTON_RoR, &CCalculatorDlg::OnBnClickedButtonRor)
	ON_BN_CLICKED(IDC_BUTTON_RoL, &CCalculatorDlg::OnBnClickedButtonRol)
	ON_BN_CLICKED(IDC_BUTTON_And, &CCalculatorDlg::OnBnClickedButtonAnd)
	ON_BN_CLICKED(IDC_BUTTON_Not, &CCalculatorDlg::OnBnClickedButtonNot)
	ON_BN_CLICKED(IDC_BUTTON_Xor, &CCalculatorDlg::OnBnClickedButtonXor)
	ON_BN_CLICKED(IDC_BUTTON_Or, &CCalculatorDlg::OnBnClickedButtonOr)
	ON_BN_CLICKED(IDC_BUTTON_Rsh, &CCalculatorDlg::OnBnClickedButtonRsh)
	ON_BN_CLICKED(IDC_BUTTON_Lsh, &CCalculatorDlg::OnBnClickedButtonLsh)
	ON_BN_CLICKED(IDC_BUTTON_EQUAL, &CCalculatorDlg::OnBnClickedButtonEqual)
	ON_BN_CLICKED(IDC_BUTTON_SWITCH, &CCalculatorDlg::OnBnClickedButtonSwitch)
END_MESSAGE_MAP()


// CCalculatorDlg message handlers

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_Font1.CreatePointFont(150, _T("Arial Bold"));
	m_Button_0.SetFont(&m_Font1);
	m_Button_1.SetFont(&m_Font1);
	m_Button_2.SetFont(&m_Font1);
	m_Button_3.SetFont(&m_Font1);
	m_Button_4.SetFont(&m_Font1);
	m_Button_5.SetFont(&m_Font1);
	m_Button_6.SetFont(&m_Font1);
	m_Button_7.SetFont(&m_Font1);
	m_Button_8.SetFont(&m_Font1);
	m_Button_9.SetFont(&m_Font1);
	m_Button_Switch.SetFont(&m_Font1);
	m_Font2 = new CFont();
	m_Font2->CreatePointFont(310, _T("Arial Bold"));
	GetDlgItem(IDC_ENTRY_VALUE)->SetFont(m_Font2);

	init();

	baseChosen = BASE_DEC;
	m_Button_Dec.EnableWindow(FALSE);
	m_Button_A.EnableWindow(FALSE);
	m_Button_B.EnableWindow(FALSE);
	m_Button_C.EnableWindow(FALSE);
	m_Button_D.EnableWindow(FALSE);
	m_Button_E.EnableWindow(FALSE);
	m_Button_F.EnableWindow(FALSE);
	m_Button_Dot.EnableWindow(FALSE);

	/*CRect rect;
	CWnd *pWnd = GetDlgItem(IDC_ENTRY_VALUE);
	pWnd->GetWindowRect(&rect);
	m_History.Format(_T("%d"), rect.Height());*/

	UpdateData(FALSE);

	signsTurn = true;
	dotUsed = true;
	mode = INTEGER;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

//Khởi tạo trạng thái ban đầu của các biến hỗ trợ trong chương trình
void CCalculatorDlg::init()
{
	floatSignOn = false;
	if (mode == DECIMAL)
		dotUsed = false;
	else
		dotUsed = true;
	m_EntryVal = "0";
	m_HexVal = "0";
	m_DecVal = "0";
	m_BinVal = "0";
	m_History = "";
	m_History_Bin = "";
	m_History_Dec = "";
	m_History_Hex = "";
	tmpL = "";
	tmpR = "";
	m_recentOperator = '+';
	m_entry.StringToQfloat("0");
	m_res.StringToQfloat("0");
	m_int_entry = "0";
	m_int_res = "0";
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#pragma region OnClieckedButtonNumbers
//Chỉnh font chữ và kích thước chữ cho hộp giá trị nhập
void CCalculatorDlg::setEnTryValFont()
{
	int len = m_EntryVal.GetLength();
	if (len >= 20) {
		delete m_Font2;
		m_Font2 = new CFont;
		m_Font2->CreatePointFont(310 - ((len - 20) << 1), _T("Arial Bold"));
		GetDlgItem(IDC_ENTRY_VALUE)->SetFont(m_Font2);
	}
	else {
		delete m_Font2;
		m_Font2 = new CFont;
		m_Font2->CreatePointFont(310, _T("Arial Bold"));
		GetDlgItem(IDC_ENTRY_VALUE)->SetFont(m_Font2);
	}
}

//Hàm được gói khi nhập toán hạng
void CCalculatorDlg::onBnClickedButtonOperand(CString operand)
{
	if (m_EntryVal.GetLength() >= 128)
		return;
	
	if (!signsTurn && m_EntryVal[m_EntryVal.GetLength() - 1] != '.')
		m_EntryVal = operand;
	else
		UPDATE_ENTRY(m_EntryVal, operand/* + operand + operand + operand + operand + operand + operand + operand*/);

	signsTurn = true;

	setEnTryValFont();
	UpdateData(FALSE);
	placeCursorToEnd(IDC_EDIT_HISTORY);
}

//Các hàm gọi khi nhập giá trị
void CCalculatorDlg::OnBnClickedButton0()
{
	if (m_EntryVal.GetLength() >= 128)
		return;
	
	if (m_EntryVal != "0" || floatSignOn) {
		m_EntryVal += "0";
		setEnTryValFont();
		UpdateData(FALSE);
		placeCursorToEnd(IDC_EDIT_HISTORY);
	}
	else
		if (!signsTurn) {
			setEnTryValFont();
			UpdateData(FALSE);
			placeCursorToEnd(IDC_EDIT_HISTORY);
			signsTurn = true;
		}
}


void CCalculatorDlg::OnBnClickedButton1()
{
	if (m_EntryVal.GetLength() >= 128)
		return;

	if (floatSignOn || m_EntryVal != "0")
		m_EntryVal += "1";
	else
		m_EntryVal = "1";

	signsTurn = true;

	setEnTryValFont();
	UpdateData(FALSE);
	placeCursorToEnd(IDC_EDIT_HISTORY);
}


void CCalculatorDlg::OnBnClickedButton2()
{
	onBnClickedButtonOperand(_T("2"));
}


void CCalculatorDlg::OnBnClickedButton3()
{
	onBnClickedButtonOperand(_T("3"));
}


void CCalculatorDlg::OnBnClickedButton4()
{
	onBnClickedButtonOperand(_T("4"));
}


void CCalculatorDlg::OnBnClickedButton5()
{
	onBnClickedButtonOperand(_T("5"));
}


void CCalculatorDlg::OnBnClickedButton6()
{
	onBnClickedButtonOperand(_T("6"));
}


void CCalculatorDlg::OnBnClickedButton7()
{
	onBnClickedButtonOperand(_T("7"));
}


void CCalculatorDlg::OnBnClickedButton8()
{
	onBnClickedButtonOperand(_T("8"));
}


void CCalculatorDlg::OnBnClickedButton9()
{
	onBnClickedButtonOperand(_T("9"));
}


void CCalculatorDlg::OnBnClickedButtonA()
{
	onBnClickedButtonOperand(_T("A"));
}


void CCalculatorDlg::OnBnClickedButtonB()
{
	onBnClickedButtonOperand(_T("B"));
}


void CCalculatorDlg::OnBnClickedButtonC()
{
	onBnClickedButtonOperand(_T("C"));
}


void CCalculatorDlg::OnBnClickedButtonD()
{
	onBnClickedButtonOperand(_T("D"));
}


void CCalculatorDlg::OnBnClickedButtonE()
{
	onBnClickedButtonOperand(_T("E"));
}


void CCalculatorDlg::OnBnClickedButtonF()
{
	onBnClickedButtonOperand(_T("F"));
}
//---------------------------------------------------------------
#pragma endregion

//Hàm gọi khi nhấn backspace
void CCalculatorDlg::OnBnClickedButtonBackspace()
{
	if (!signsTurn)
		return;
	if (m_EntryVal.GetLength() == 1)
		m_EntryVal = "0";
	else {
		if (m_EntryVal[m_EntryVal.GetLength() - 1] == '.')
			dotUsed = false;
		m_EntryVal.Delete(m_EntryVal.GetLength() - 1);
	}

	setEnTryValFont();
	UpdateData(FALSE);
	placeCursorToEnd(IDC_EDIT_HISTORY);
}

//Hàm gọi khi nhấn phím chuyển dấu
void CCalculatorDlg::OnBnClickedButtonSign()
{
	/*if (m_EntryVal == "0")
			return;
		if (m_EntryVal[0] == '-')
			m_EntryVal.Delete(0);
		else
			m_EntryVal = _T("-") + m_EntryVal;*/
	if (mode == DECIMAL) {
		Qfloat tmp("0");
		m_entry = tmp - m_entry;
		if (baseChosen == BASE_DEC)
			m_EntryVal = m_entry.ToStringDec().c_str();
		else
			m_EntryVal = m_entry.ToStringBin().c_str();
	}
	else {
		QINT tmp;
		m_int_entry = tmp - m_int_entry;
		if (baseChosen == BASE_DEC)
			m_EntryVal = m_int_entry.PrintQintDec().c_str();
		else
			if (baseChosen == BASE_BIN)
				m_EntryVal = m_int_entry.PrintQintBin().c_str();
			else
				m_EntryVal = m_int_entry.PrintQintHex().c_str();
	}

	signsTurn = true;
	setEnTryValFont();
	UpdateData(FALSE);
	placeCursorToEnd(IDC_EDIT_HISTORY);
}

//Hàm gọi khi nhập dấu '.'
void CCalculatorDlg::OnBnClickedButtonDot()
{
	if (dotUsed)
		return;

	m_EntryVal += ".";
	dotUsed = true;
	
	setEnTryValFont();

	UpdateData(FALSE);
}

//Hàm gọi trước khi vẽ lại 1 thành phần trong giao diện
HBRUSH CCalculatorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if (pWnd->GetDlgCtrlID() == IDC_ENTRY_VALUE) {
		CT2CA pszConvertedAnsiString(m_EntryVal);
		string tmp(pszConvertedAnsiString);
		if (mode == DECIMAL) {
			if (baseChosen == BASE_DEC) {
				m_DecVal = m_EntryVal;
				m_entry.StringToQfloat(tmp);
				m_BinVal = m_entry.ToStringBin().c_str();
			}
			else {
				m_BinVal = m_EntryVal;
				m_entry.StringBinToDec(tmp);
				m_DecVal = m_entry.ToStringDec().c_str();
			}
		}
		else {
			if (baseChosen == BASE_DEC) {
				m_DecVal = m_EntryVal;
				m_int_entry = tmp;
				m_BinVal = m_int_entry.PrintQintBin().c_str();
				m_HexVal = m_int_entry.PrintQintHex().c_str();
			}
			else 
				if (baseChosen == BASE_BIN) {
					m_BinVal = m_EntryVal;
					m_int_entry.ScanQIntFromBinString(tmp);
					m_DecVal = m_int_entry.PrintQintDec().c_str();
					m_HexVal = m_int_entry.PrintQintHex().c_str();
				}
				else {
					m_HexVal = m_EntryVal;
					m_int_entry.ScanQIntFromHexString(tmp);
					m_BinVal = m_int_entry.PrintQintBin().c_str();
					m_DecVal = m_int_entry.PrintQintDec().c_str();
				}
		}
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

#pragma region OnBnClickedButtonBase
//Hàm gọi khi nhấn chuyển đổi giữa chế độ Qint và Qfloat
void CCalculatorDlg::OnBnClickedButtonSwitch()
{
	if (mode == INTEGER) {
		if (baseChosen == BASE_HEX) {
			m_Button_A.EnableWindow(FALSE);
			m_Button_B.EnableWindow(FALSE);
			m_Button_C.EnableWindow(FALSE);
			m_Button_D.EnableWindow(FALSE);
			m_Button_E.EnableWindow(FALSE);
			m_Button_F.EnableWindow(FALSE);
			m_Button_Dec.EnableWindow(FALSE);
			baseChosen = BASE_DEC;
		}
		m_Button_Switch.SetWindowText(_T("Integer"));
		m_Button_Hex.EnableWindow(FALSE);
		if (baseChosen == BASE_DEC) {
			m_Button_Dot.EnableWindow(TRUE);
			dotUsed = false;
		}
		m_Button_Lsh.EnableWindow(FALSE);
		m_Button_Rsh.EnableWindow(FALSE);
		m_Button_Or.EnableWindow(FALSE);
		m_Button_Xor.EnableWindow(FALSE);
		m_Button_Not.EnableWindow(FALSE);
		m_Button_And.EnableWindow(FALSE);
		m_Button_RoL.EnableWindow(FALSE);
		m_Button_RoR.EnableWindow(FALSE);
		mode = DECIMAL;
	}
	else {
		floatSignOn = false;
		m_Button_Switch.SetWindowText(_T("Decimal"));
		m_Button_Hex.EnableWindow(TRUE);
		m_Button_Dot.EnableWindow(FALSE);
		m_Button_Lsh.EnableWindow(TRUE);
		m_Button_Rsh.EnableWindow(TRUE);
		m_Button_Or.EnableWindow(TRUE);
		m_Button_Xor.EnableWindow(TRUE);
		m_Button_Not.EnableWindow(TRUE);
		m_Button_And.EnableWindow(TRUE);
		m_Button_RoL.EnableWindow(TRUE);
		m_Button_RoR.EnableWindow(TRUE);
		mode = INTEGER;
		dotUsed = true;
	}
	init();
	setEnTryValFont();
	UpdateData(FALSE);
	signsTurn = true;
}

//Hàm gọi khi nhấn chuyển sang hệ 16
void CCalculatorDlg::OnBnClickedButtonHex()
{
	if (baseChosen == BASE_DEC) {
		m_Button_Dec.EnableWindow(TRUE);
	}
	else {
		m_Button_Bin.EnableWindow(TRUE);
		m_Button_2.EnableWindow(TRUE);
		m_Button_3.EnableWindow(TRUE);
		m_Button_4.EnableWindow(TRUE);
		m_Button_5.EnableWindow(TRUE);
		m_Button_6.EnableWindow(TRUE);
		m_Button_7.EnableWindow(TRUE);
		m_Button_8.EnableWindow(TRUE);
		m_Button_9.EnableWindow(TRUE);
	}
	m_Button_A.EnableWindow(TRUE);
	m_Button_B.EnableWindow(TRUE);
	m_Button_C.EnableWindow(TRUE);
	m_Button_D.EnableWindow(TRUE);
	m_Button_E.EnableWindow(TRUE);
	m_Button_F.EnableWindow(TRUE);

	baseChosen = BASE_HEX;
	m_EntryVal = m_HexVal;
	setEnTryValFont();
	m_History = m_History_Hex;
	m_Button_Hex.EnableWindow(FALSE);
	m_Button_0.SetFocus();
	UpdateData(FALSE);
	placeCursorToEnd(IDC_EDIT_HISTORY);
}

//Hàm gọi khi nhấn chuyển sang hệ 10
void CCalculatorDlg::OnBnClickedButtonDec()
{
	if (baseChosen == BASE_HEX) {
		m_Button_Hex.EnableWindow(TRUE);
		m_Button_A.EnableWindow(FALSE);
		m_Button_B.EnableWindow(FALSE);
		m_Button_C.EnableWindow(FALSE);
		m_Button_D.EnableWindow(FALSE);
		m_Button_E.EnableWindow(FALSE);
		m_Button_F.EnableWindow(FALSE);
	}
	else {
		m_Button_Bin.EnableWindow(TRUE);
		m_Button_2.EnableWindow(TRUE);
		m_Button_3.EnableWindow(TRUE);
		m_Button_4.EnableWindow(TRUE);
		m_Button_5.EnableWindow(TRUE);
		m_Button_6.EnableWindow(TRUE);
		m_Button_7.EnableWindow(TRUE);
		m_Button_8.EnableWindow(TRUE);
		m_Button_9.EnableWindow(TRUE);
		if (mode == DECIMAL) {
			m_Button_Dot.EnableWindow(TRUE);
			dotUsed = false;
			floatSignOn = false;
		}
	}

	baseChosen = BASE_DEC;
	m_EntryVal = m_DecVal;
	setEnTryValFont();
	m_History = m_History_Dec;
	m_Button_Dec.EnableWindow(FALSE);
	m_Button_0.SetFocus();
	UpdateData(FALSE);
	placeCursorToEnd(IDC_EDIT_HISTORY);
}

//Hàm gọi khi nhấn chuyển sang hệ 2
void CCalculatorDlg::OnBnClickedButtonBin()
{
	if (baseChosen == BASE_DEC) {
		m_Button_Dec.EnableWindow(TRUE);
		if (mode == DECIMAL) {
			m_Button_Dot.EnableWindow(FALSE);
			dotUsed = true;
		}
	}
	else {
		m_Button_Hex.EnableWindow(TRUE);
		m_Button_A.EnableWindow(FALSE);
		m_Button_B.EnableWindow(FALSE);
		m_Button_C.EnableWindow(FALSE);
		m_Button_D.EnableWindow(FALSE);
		m_Button_E.EnableWindow(FALSE);
		m_Button_F.EnableWindow(FALSE);
	}
	m_Button_2.EnableWindow(FALSE);
	m_Button_3.EnableWindow(FALSE);
	m_Button_4.EnableWindow(FALSE);
	m_Button_5.EnableWindow(FALSE);
	m_Button_6.EnableWindow(FALSE);
	m_Button_7.EnableWindow(FALSE);
	m_Button_8.EnableWindow(FALSE);
	m_Button_9.EnableWindow(FALSE);

	baseChosen = BASE_BIN;
	m_EntryVal = m_BinVal;
	setEnTryValFont();
	m_History = m_History_Bin;
	m_Button_Bin.EnableWindow(FALSE);
	m_Button_0.SetFocus();
	UpdateData(FALSE);
	placeCursorToEnd(IDC_EDIT_HISTORY);
}
#pragma endregion


#pragma region Clear
//Hàm gọi khi nhấn phím C
void CCalculatorDlg::OnBnClickedButtonClear()
{
	init();
	setEnTryValFont();
	UpdateData(FALSE);
}

//Hàm gọi khi nhấn phím Ce
void CCalculatorDlg::OnBnClickedButtonCe()
{
	m_EntryVal = "0";
	m_entry.StringToQfloat("0");
	m_int_entry = "0";
	setEnTryValFont();
	UpdateData(FALSE);
	placeCursorToEnd(IDC_EDIT_HISTORY);
}
#pragma endregion

//Cập nhật hộp entry value trong chế độ Qint
void CCalculatorDlg::updateEntryValBoxQINT()
{
	if (baseChosen == BASE_DEC)
		m_EntryVal = m_int_entry.PrintQintDec().c_str();
	else
		if (baseChosen == BASE_BIN)
			m_EntryVal = m_int_entry.PrintQintBin().c_str();
		else
			m_EntryVal = m_int_entry.PrintQintHex().c_str();
}

#pragma region OnBnClickedButtonSign
//Hàm gọi khi nhấn toán tử Ror
void CCalculatorDlg::OnBnClickedButtonRor()
{
	QINT tmp;
	if (m_EntryVal == "0" && !(m_int_entry == tmp))
		updateEntryValBoxQINT();

	if (tmpR == "") {
		tmpL = m_History;
		tmpR = m_EntryVal;
	}

	tmpR = _T("RoR(") + tmpR + _T(")");
	m_History = tmpL + tmpR;
	signsTurn = true;

	m_int_entry = m_int_entry.ror(1);
	updateEntryValBoxQINT();

	UpdateData(FALSE);
	placeCursorToEnd(IDC_EDIT_HISTORY);
}

//Hàm gọi khi nhấn toán tử Rol
void CCalculatorDlg::OnBnClickedButtonRol()
{
	QINT tmp;
	if (m_EntryVal == "0" && !(m_int_entry == tmp))
		updateEntryValBoxQINT();

	if (tmpR == "") {
		tmpL = m_History;
		tmpR = m_EntryVal;
	}

	tmpR = _T("RoL(") + tmpR + _T(")");
	m_History = tmpL + tmpR;
	signsTurn = true;

	m_int_entry = m_int_entry.rol(1);
	updateEntryValBoxQINT();

	UpdateData(FALSE);
	placeCursorToEnd(IDC_EDIT_HISTORY);
}

//Hàm gọi khi nhấn toán tử Not
void CCalculatorDlg::OnBnClickedButtonNot()
{
	QINT tmp;
	if (m_EntryVal == "0" && !(m_int_entry == tmp))
		updateEntryValBoxQINT();

	if (tmpR == "") {
		tmpL = m_History;
		tmpR = m_EntryVal;
	}

	tmpR = _T("!") + tmpR;
	m_History = tmpL + tmpR;
	signsTurn = true;

	m_int_entry = ~m_int_entry;
	updateEntryValBoxQINT();

	UpdateData(FALSE);
	placeCursorToEnd(IDC_EDIT_HISTORY);
}

//Đặt con trỏ ở cuối dòng text của thành phần id
void CCalculatorDlg::placeCursorToEnd(UINT id)
{
	CEdit* e = (CEdit*)GetDlgItem(id);
	e->SetFocus();
	e->SetSel(-1);
	e->HideCaret();
}

//Tính toán chế độ Qfloat
void CCalculatorDlg::calculate()
{
	switch (m_recentOperator) {
	case '+':
		m_res = m_res + m_entry;
		break;
	case '-':
		m_res = m_res - m_entry;
		break;
	case 'x':
		m_res = m_res * m_entry;
		break;
	case '/':
		m_res = m_res / m_entry;
		break;
	}
}

//Tính toán chế độ Qint
void CCalculatorDlg::calculateINT()
{
	switch (m_recentOperator) {
	case '+':
		m_int_res = m_int_res + m_int_entry;
		break;
	case '-':
		m_int_res = m_int_res - m_int_entry;
		break;
	case 'x':
		m_int_res = m_int_res * m_int_entry;
		break;
	case '/':
		m_int_res = m_int_res / m_int_entry;
		break;
	case '<': {
		QINT tmp;
		if (m_int_entry >= tmp) {
			tmp = "128";
			if (m_int_entry < tmp)
				m_int_res = m_int_res << m_int_entry.QintToInt32();
			else
				m_EntryVal = "Result not defined";
		}
		else
			m_EntryVal = "Result not defined";
	}
			  break;
	case '>': {
		QINT tmp;
		if (m_int_entry >= tmp) {
			tmp = "128";
			if (m_int_entry < tmp)
				m_int_res = m_int_res >> m_int_entry.QintToInt32();
			else
				m_EntryVal = "Result not defined";
		}
		else
			m_EntryVal = "Result not defined";
	}
			  break;
	case '&':
		m_int_res = m_int_res & m_int_entry;
		break;
	case '|':
		m_int_res = m_int_res | m_int_entry;
		break;
	case '^':
		m_int_res = m_int_res ^ m_int_entry;
		break;
	}
}

//Hàm tổng quát gọi khi nhập toán tử
void CCalculatorDlg::onBnClickedButtonOperator(CString op)
{
	if (!signsTurn)
		return;

	if (tmpR == "") {
		m_History += m_EntryVal;
		if (mode == DECIMAL) {
			m_History_Bin += m_entry.ToStringBin().c_str();
			m_History_Dec += m_entry.ToStringDec().c_str();
		}
		else {
			m_History_Bin += m_int_entry.PrintQintBin().c_str();
			m_History_Dec += m_int_entry.PrintQintDec().c_str();
			m_History_Hex += m_int_entry.PrintQintHex().c_str();
		}
	}
	m_History += op;
	m_History_Bin += op;
	m_History_Dec += op;
	if (mode == INTEGER)
		m_History_Hex += op;

	if (mode == DECIMAL)
		calculate();
	else
		calculateINT();

	UpdateData(FALSE);
	placeCursorToEnd(IDC_EDIT_HISTORY);

	if (m_EntryVal != "Result not defined") {
		signsTurn = false;
		m_EntryVal = "0";
		tmpR = "";
	}
	else {
		init();
	}
	
	if (mode == DECIMAL && baseChosen == BASE_DEC)
		dotUsed = false;

	m_recentOperator = op[1];
}

//Các hàm gọi khi nhập toán tử
void CCalculatorDlg::OnBnClickedButtonPlus()
{
	onBnClickedButtonOperator(_T(" + "));
}



void CCalculatorDlg::OnBnClickedButtonSubtract()
{
	onBnClickedButtonOperator(_T(" - "));
}


void CCalculatorDlg::OnBnClickedButtonMultiply()
{
	onBnClickedButtonOperator(_T(" x "));
}


void CCalculatorDlg::OnBnClickedButtonDivide()
{
	onBnClickedButtonOperator(_T(" / "));
}


void CCalculatorDlg::OnBnClickedButtonAnd()
{
	onBnClickedButtonOperator(_T(" & "));
}


void CCalculatorDlg::OnBnClickedButtonXor()
{
	onBnClickedButtonOperator(_T(" ^ "));
}


void CCalculatorDlg::OnBnClickedButtonOr()
{
	onBnClickedButtonOperator(_T(" | "));
}


void CCalculatorDlg::OnBnClickedButtonRsh()
{
	onBnClickedButtonOperator(_T(" >> "));
}


void CCalculatorDlg::OnBnClickedButtonLsh()
{
	onBnClickedButtonOperator(_T(" << "));
}
//----------------------------------------------------

//Hàm gọi khi nhấn Enter hay =
void CCalculatorDlg::OnBnClickedButtonEqual()
{
	//Do calculating
	if (mode == DECIMAL) {
		calculate();
		if (baseChosen == BASE_DEC)
			m_EntryVal = m_res.ToStringDec().c_str();
		else
			if (baseChosen == BASE_BIN)
				m_EntryVal = m_res.ToStringBin().c_str();
	}
	else {
		calculateINT();
		if (m_EntryVal != "Result not defined") {
			if (baseChosen == BASE_DEC)
				m_EntryVal = m_int_res.PrintQintDec().c_str();
			else
				if (baseChosen == BASE_BIN)
					m_EntryVal = m_int_res.PrintQintBin().c_str();
				else
					m_EntryVal = m_int_res.PrintQintHex().c_str();
		}
	}

	tmpR = "";
	m_History = "";
	m_History_Bin = "";
	m_History_Dec = "";
	m_History_Hex = "";
	m_res.StringToQfloat("0");
	m_int_res = "0";
	m_recentOperator = '+';
	setEnTryValFont();
	UpdateData(FALSE);
	if (m_EntryVal == "Result not defined")
		m_EntryVal = "0";
	if (m_EntryVal.Find('.', 0) != -1)
		dotUsed = true;

}
#pragma endregion

//Hàm gọi trước khi dịch 1 message
BOOL CCalculatorDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_CHAR) {
		switch (pMsg->wParam) {
		case 0x30:
			OnBnClickedButton0();
			break;
		case 0x31:
			OnBnClickedButton1();
			break;
		case 0x32:
			if (baseChosen != BASE_BIN)
				OnBnClickedButton2();
			break;
		case 0x33:
			if (baseChosen != BASE_BIN)
				OnBnClickedButton3();
			break;
		case 0x34:
			if (baseChosen != BASE_BIN)
				OnBnClickedButton4();
			break;
		case 0x35:
			if (baseChosen != BASE_BIN)
				OnBnClickedButton5();
			break;
		case 0x36:
			if (baseChosen != BASE_BIN)
				OnBnClickedButton6();
			break;
		case 0x37:
			if (baseChosen != BASE_BIN)
				OnBnClickedButton7();
			break;
		case 0x38:
			if (baseChosen != BASE_BIN)
				OnBnClickedButton8();
			break;
		case 0x39:
			if (baseChosen != BASE_BIN)
				OnBnClickedButton9();
			break;
		case 0x41:
			if (baseChosen == BASE_HEX)
				OnBnClickedButtonA();
			break;
		case 0x42:
			if (baseChosen == BASE_HEX)
				OnBnClickedButtonB();
			break;
		case 0x43:
			if (baseChosen == BASE_HEX)
				OnBnClickedButtonC();
			break;
		case 0x44:
			if (baseChosen == BASE_HEX)
				OnBnClickedButtonD();
			break;
		case 0x45:
			if (baseChosen == BASE_HEX)
				OnBnClickedButtonE();
			break;
		case 0x46:
			if (baseChosen == BASE_HEX)
				OnBnClickedButtonF();
			break;
		case 42:
			OnBnClickedButtonMultiply();
			break;
		case 43:
			OnBnClickedButtonPlus();
			break;
		case 45:
			OnBnClickedButtonSubtract();
			break;
		case 47:
			OnBnClickedButtonDivide();
			break;
		case 61:
			OnBnClickedButtonEqual();
			break;
		case 46:
			//if (mode == DECIMAL && baseChosen == BASE_DEC)
			if (dotUsed == false)
				OnBnClickedButtonDot();
			break;
		case 8:
			OnBnClickedButtonBackspace();
			break;
		case 0x53:
			if (mode == DECIMAL && baseChosen == BASE_BIN)
				floatSignOn = !floatSignOn;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}