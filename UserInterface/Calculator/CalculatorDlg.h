
// CalculatorDlg.h : header file
//

#pragma once
#define BASE_HEX 16
#define BASE_DEC 10
#define BASE_BIN 2
#define DECIMAL 69
#define INTEGER 96
#define UPDATE_ENTRY(entry, string) entry == "0" ? entry = string : entry += string

#include "QFloat.h"
#include "QInt.h"

// CCalculatorDlg dialog
class CCalculatorDlg : public CDialogEx
{
// Construction
public:
	CCalculatorDlg(CWnd* pParent = nullptr);	// standard constructor
	virtual ~CCalculatorDlg() {
		delete m_Font2;
	}

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	int baseChosen;
	int mode;
	bool signsTurn, dotUsed, floatSignOn;
	CFont m_Font1, *m_Font2;
	Qfloat m_entry, m_res;
	QINT m_int_entry, m_int_res;
	char m_recentOperator;

	void init();
	void placeCursorToEnd(UINT id);
	void onBnClickedButtonOperator(CString op);
	void onBnClickedButtonOperand(CString operand);
	void setEnTryValFont();
	void calculate();
	void calculateINT();
	void updateEntryValBoxQINT();

	CString m_EntryVal;
	CString m_History, m_History_Bin, m_History_Dec, m_History_Hex;
	CString m_HexVal, m_DecVal, m_BinVal;
	CString tmpL, tmpR;//Xử lý in các toán tử RoR, RoL, Not

	CButton m_Button_Dec;
	CButton m_Button_Hex;
	CButton m_Button_Bin;
	CButton m_Button_A;
	CButton m_Button_B;
	CButton m_Button_C;
	CButton m_Button_D;
	CButton m_Button_E;
	CButton m_Button_F;
	CButton m_Button_Dot;
	CButton m_Button_0;
	CButton m_Button_1;
	CButton m_Button_2;
	CButton m_Button_3;
	CButton m_Button_4;
	CButton m_Button_5;
	CButton m_Button_6;
	CButton m_Button_7;
	CButton m_Button_8;
	CButton m_Button_9;
	CButton m_Button_Switch;
	CButton m_Button_Lsh;
	CButton m_Button_Rsh;
	CButton m_Button_Or;
	CButton m_Button_Xor;
	CButton m_Button_Not;
	CButton m_Button_And;
	CButton m_Button_RoL;
	CButton m_Button_RoR;
public:
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButtonA();
	afx_msg void OnBnClickedButtonB();
	afx_msg void OnBnClickedButtonC();
	afx_msg void OnBnClickedButtonD();
	afx_msg void OnBnClickedButtonE();
	afx_msg void OnBnClickedButtonF();
	afx_msg void OnBnClickedButtonBackspace();
	afx_msg void OnBnClickedButtonSign();
	afx_msg void OnBnClickedButtonDot();
	afx_msg void OnBnClickedButtonHex();
	afx_msg void OnBnClickedButtonDec();
	afx_msg void OnBnClickedButtonBin();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonCe();
	afx_msg void OnBnClickedButtonPlus();
	afx_msg void OnBnClickedButtonSubtract();
	afx_msg void OnBnClickedButtonMultiply();
	afx_msg void OnBnClickedButtonDivide();
	afx_msg void OnBnClickedButtonRor();
	afx_msg void OnBnClickedButtonRol();
	afx_msg void OnBnClickedButtonAnd();
	afx_msg void OnBnClickedButtonNot();
	afx_msg void OnBnClickedButtonXor();
	afx_msg void OnBnClickedButtonOr();
	afx_msg void OnBnClickedButtonRsh();
	afx_msg void OnBnClickedButtonLsh();
	afx_msg void OnBnClickedButtonEqual();
	afx_msg void OnBnClickedButtonSwitch();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
	BOOL PreTranslateMessage(MSG* pMsg);
};
