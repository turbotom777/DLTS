; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CVoltageOutDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "dltsgui.h"
LastPage=0

ClassCount=16
Class1=CBoontonRange
Class2=CChildFrame
Class3=CConsole
Class4=CDLTSguiApp
Class5=CAboutDlg
Class6=CDLTSguiDoc
Class7=CDLTSguiView
Class8=CGraphProperties
Class9=CGraphRange
Class10=CListFrame
Class11=CMainFrame
Class12=CParameters
Class13=CPropertyDlg
Class14=CSizingControlBar
Class15=CVoltageOutDialog
Class16=CWorkspaceWnd

ResourceCount=7
Resource1=IDR_TOOLBAR_ACTION (English (U.S.))
Resource2=IDR_DLTSGUTYPE (English (U.S.))
Resource3=IDD_GRAPH_RANGE (English (U.S.))
Resource4=IDD_DIALOG_OUT_VOLTAGE
Resource5=IDD_PARAMETER_DIALOG
Resource6=IDD_ABOUTBOX (English (U.S.))
Resource7=IDR_MAINFRAME (English (U.S.))

[CLS:CBoontonRange]
Type=0
BaseClass=CDialog
HeaderFile=BoontonRange.h
ImplementationFile=BoontonRange.cpp

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp

[CLS:CConsole]
Type=0
BaseClass=CSizingControlBar
HeaderFile=Console.h
ImplementationFile=Console.cpp

[CLS:CDLTSguiApp]
Type=0
BaseClass=CWinApp
HeaderFile=DLTSgui.h
ImplementationFile=DLTSgui.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=DLTSgui.cpp
ImplementationFile=DLTSgui.cpp
LastObject=CAboutDlg

[CLS:CDLTSguiDoc]
Type=0
BaseClass=CDocument
HeaderFile=DLTSguiDoc.h
ImplementationFile=DLTSguiDoc.cpp
Filter=N
VirtualFilter=DC
LastObject=CDLTSguiDoc

[CLS:CDLTSguiView]
Type=0
BaseClass=CView
HeaderFile=DLTSguiView.h
ImplementationFile=DLTSguiView.cpp

[CLS:CGraphProperties]
Type=0
BaseClass=CDialog
HeaderFile=GraphProperties.h
ImplementationFile=GraphProperties.cpp
Filter=D
VirtualFilter=dWC

[CLS:CGraphRange]
Type=0
BaseClass=CDialog
HeaderFile=GraphRange.h
ImplementationFile=GraphRange.cpp
LastObject=CGraphRange

[CLS:CListFrame]
Type=0
BaseClass=CWnd
HeaderFile=ListFrame.h
ImplementationFile=ListFrame.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CParameters]
Type=0
BaseClass=CDialog
HeaderFile=Parameters.h
ImplementationFile=Parameters.cpp

[CLS:CPropertyDlg]
Type=0
BaseClass=CDialog
HeaderFile=PropertyDlg.h
ImplementationFile=PropertyDlg.cpp
LastObject=CPropertyDlg

[CLS:CSizingControlBar]
Type=0
BaseClass=baseCSizingControlBar
HeaderFile=SIZECBAR.H
ImplementationFile=SIZECBAR.CPP

[CLS:CVoltageOutDialog]
Type=0
BaseClass=CDialog
HeaderFile=VoltageOutDialog.h
ImplementationFile=VoltageOutDialog.cpp
LastObject=IDC_EDIT_VOTAGE_OUT

[CLS:CWorkspaceWnd]
Type=0
BaseClass=baseCDockingBar
HeaderFile=WorkspaceWnd.h
ImplementationFile=WorkspaceWnd.cpp

[DLG:IDD_DIALOG_BOONTON_RANGE]
Type=1
Class=CBoontonRange

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDD_GRAPH_RANGE]
Type=1
Class=CGraphProperties

[DLG:IDD_PARAMETER_DIALOG]
Type=1
Class=CParameters
ControlCount=43
Control1=IDC_STATIC,button,1342177287
Control2=IDC_EDIT_NUM_AVERAGING,edit,1350631552
Control3=IDC_EDIT_PULSE_WIDTH,edit,1350631552
Control4=IDC_EDIT_T1,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT_PULSE_VOLTAGE,edit,1350631552
Control13=IDOK,button,1342242816
Control14=IDCANCEL,button,1342242816
Control15=IDC_EDIT_T2,edit,1350631552
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_EDIT_REVERSE_VOLTAGE,edit,1350631552
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_EDIT_TEMP_START,edit,1350631552
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,button,1342177287
Control24=IDC_EDIT_TEMP_END,edit,1350631552
Control25=IDC_STATIC,static,1342308352
Control26=IDC_EDIT_TEMP_STEP,edit,1350631552
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,button,1342177287
Control29=IDC_EDIT_DELAY,edit,1350631552
Control30=IDC_STATIC,static,1342308352
Control31=IDC_EDIT_GAIN,edit,1350631552
Control32=IDC_STATIC,static,1342308352
Control33=IDC_CHECK_SINGLE_TEMP,button,1342242851
Control34=IDC_RADIO_RANGE_2,button,1342308361
Control35=IDC_RADIO_RANGE_20,button,1342177289
Control36=IDC_RADIO_RANGE_200,button,1342177289
Control37=IDC_RADIO_RANGE_2000,button,1342177289
Control38=IDC_STATIC,button,1342177287
Control39=IDC_STATIC,static,1342308352
Control40=IDC_STATIC,static,1342308352
Control41=IDC_STATIC,static,1342308352
Control42=IDC_STATIC,static,1342308352
Control43=IDC_EDIT_TEMP_DEVIANCE,edit,1350631552

[DLG:IDD_DIALOG_OUT_VOLTAGE]
Type=1
Class=CVoltageOutDialog
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_VOTAGE_OUT,edit,1350631552

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_DLTSGUTYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_START_CT
Command2=ID_FILE_STOP_MEASUREMENT
Command3=ID_FILE_CLOSE
Command4=ID_FILE_OPEN
Command5=ID_FILE_SAVE
Command6=ID_FILE_SAVE_AS
Command7=ID_FILE_IMPORT
Command8=ID_FILE_EXPORTSTATISTIC
Command9=ID_FILE_PRINT
Command10=ID_FILE_PRINT_PREVIEW
Command11=ID_FILE_PRINT_SETUP
Command12=ID_FILE_MRU_FILE1
Command13=ID_APP_EXIT
Command14=ID_EDIT_UNDO
Command15=ID_EDIT_CUT
Command16=ID_EDIT_COPY
Command17=ID_EDIT_PASTE
Command18=ID_WRITE_VOLTAGE
Command19=ID_EDIT_PROPERTIES
Command20=ID_EDIT_BOONTON_ZERO
Command21=ID_VIEW_PROJECT_VIEW
Command22=ID_VIEW_TOOLBAR
Command23=ID_VIEW_STATUS_BAR
Command24=ID_VIEW_ACTION_BAR
Command25=ID_VIEW_CONSOLE_BAR
Command26=ID_WINDOW_NEW
Command27=ID_WINDOW_CASCADE
Command28=ID_WINDOW_TILE_HORZ
Command29=ID_WINDOW_ARRANGE
Command30=ID_VISIBLE_AREA
Command31=ID_GRAPH_CT
Command32=ID_GRAPH_DLTS
Command33=ID_GRAPH_DOUBLE_BC
Command34=ID_GRAPH_LOKIN
Command35=ID_APP_ABOUT
CommandCount=35

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_GRAPH_RANGE (English (U.S.))]
Type=1
Class=CGraphRange
ControlCount=16
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_MAX_X,edit,1350631552
Control4=IDC_MIN_X,edit,1350631552
Control5=IDC_MIN_Y,edit,1350631552
Control6=IDC_MAX_Y,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_APP_ABOUT
CommandCount=5

[TB:IDR_TOOLBAR_ACTION (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_START_CT
Command2=ID_FILE_STOP_MEASUREMENT
CommandCount=2

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

