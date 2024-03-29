#include <stdio.h>
#include "service.h"
#include "TrafficAlgo.h"
#include <windows.h>
#include "resources.h"
#include "ClientFuncs.h"
#include "service.h"
#include <CommCtrl.h>
#include <d2d1.h>
int kain() {
	node* nodes = initialSetup();
	for (int i = 0; i < MAX_JUNCS; i++) {
		if (nodes[i].id == -1) {
			continue;
		}
		printf("Node id is %d coordinates(%d , %d) \n", nodes[i].id, nodes[i].x, nodes[i].y);
		for (int j = 0; j < MAX_ROADS; j++) {
			if (nodes[i].roads[j] == NULL) {
				continue;
			}
			printf("Road is from %d to %d with capacity %d and distance %f \n", nodes[i].id, nodes[i].roads[j]->to, nodes[i].roads[j]->capacity, nodes[i].roads[j]->dis);
		}
		printf("New junction \n");
	}

	int arr[NUM_VEHICLES][MAX_ROADS];
	SfindPaths(arr);
	for (int i = 0; i < NUM_VEHICLES; i++) {
		for (int j = 0; j < MAX_ROADS; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	addOperation('n', 1, 2 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0);
	addOperation('n', 2, 0, 0, 0, 0, 0, 0, 0 , 0 , 0);
	addOperation('r', 0, 0, 4, 0, 2, 0, 0, 0 , 0, 0);
	addOperation('r' , 0 , 0 , 5 , 4 , 2 , 0 , 0 , 0 , 0 , 0);
	addOperation('r', 0, 0, 2, 5, 3, 0, 0, 0 ,0 , 0);
	addOperation('r', 0, 0, 2, 4, 1, 0, 0, 0 ,0 , 0);
	addOperation('d', 0, 0, 0, 0, 0, 0, 0, 0,0 , 5);
	printf("Done operations \n \n");
	nodes = refreshSetup();
	for (int i = 0; i < MAX_JUNCS; i++) {
		if (nodes[i].id == -1) {
			continue;
		}
		printf("Node id is %d coordinates(%d , %d) \n", nodes[i].id, nodes[i].x, nodes[i].y);
		for (int j = 0; j < MAX_ROADS; j++) {
			if (nodes[i].roads[j] == NULL) {
				continue;
			}
			printf("Road is from %d to %d with capacity %d and distance %f \n", nodes[i].id, nodes[i].roads[j]->to, nodes[i].roads[j]->capacity, nodes[i].roads[j]->dis);
		}
		printf("New junction \n");
	}
	SfindPaths(arr);
	for (int i = 0; i < NUM_VEHICLES; i++) {
		for (int j = 0; j < MAX_ROADS; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}

	return 0;
}

const char g_szClassName[] = "myWindowClass";

HWND hwnd_nodeInfoPosXEdit;
HWND hwnd_nodeInfoPosYEdit;
HWND hwnd_AddNodeButton;
HWND hwnd_NodesLB;
HWND hwnd_NodeDelButton;
node* selectedNode;
road* selectedRoad;
HWND hwnd_listView;
HWND hwnd_capacity;
HWND hwnd_capacitySaveButton;
HWND hwnd_addRoadFrom;
HWND hwnd_addRoadTo;
HWND hwnd_addRoadcapacity;
WNDCLASSEX outputWindow;
HWND hwnd_outputWin;
HWND hwnd_srcEdit;
HWND hwnd_destEdit;
HWND hwnd_showPathLB;
road* roadVect[MAX_ROADS];
int arr[NUM_VEHICLES][MAX_ROADS];

//window2
HWND hwnd_VehiclesLB;
HWND hwnd_pathLB;
HWND hwnd_OutputLB;

void createWindowControls(HWND hwnd);

void fillVehiclesLB(HWND hwnd) {
    wchar_t strInt[3];
    HWND hwnd_SelectVehicleL = CreateWindowW(L"Static", L"Select a vehicle", WS_VISIBLE | WS_CHILD, 20, 10, 150, 30, hwnd, NULL, NULL, NULL);
    hwnd_VehiclesLB = CreateWindowW(L"ListBox", NULL, WS_VISIBLE | WS_CHILD | LBS_STANDARD | LBS_NOTIFY, 20, 50, 400, 200, hwnd, (HMENU)SELECT_VEHICLE, NULL, NULL);
    for (int i = 0; i < MAX_JUNCS; i++) {
        tostring(strInt, i);
        // MessageBox(NULL, )
        SendMessageW(hwnd_VehiclesLB, LB_ADDSTRING, NULL, (LPARAM)strInt);
    }
}

void fillPathLB(HWND hwnd, int arr[]) {
    wchar_t strInt[3];
    HWND hwnd_OutputL = CreateWindowW(L"Static", L"Path taken by vehicle is :", WS_VISIBLE | WS_CHILD, 20, 300, 150, 30, hwnd, NULL, NULL, NULL);
    hwnd_OutputLB = CreateWindowW(L"ListBox", NULL, WS_VISIBLE | WS_CHILD | LBS_STANDARD | LBS_NOTIFY, 20, 350, 400, 200, hwnd, NULL, NULL, NULL);
    SendMessageW(hwnd_OutputLB, LB_ADDSTRING, NULL, L"End");
    for (int i = 0; i < MAX_JUNCS; i++) {
        if (arr[i] == -1) break;
        tostring(strInt, arr[i]);
        // MessageBox(NULL, )
        SendMessageW(hwnd_OutputLB, LB_ADDSTRING, NULL, (LPARAM)strInt);
    }
}

LRESULT CALLBACK outputProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    
    switch (msg)
    {
    case WM_CREATE:
    {
        
        SfindPaths(&arr);
        int arr2 = 3;
        fillVehiclesLB(hwnd);
        //displaying output
        wchar_t str[5];
        refreshSetup();
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId) {
        case SELECT_VEHICLE:
        {
            switch (HIWORD(wParam)) {
                case LBN_SELCHANGE:
                {
                    int count = SendMessage(hwnd_VehiclesLB, LB_GETCOUNT, 0, 0);
                    int iSelected = -1;

                    for (int i = 0; i < count; i++)
                    {

                        if (SendMessage(hwnd_VehiclesLB, LB_GETSEL, i, 0) > 0)
                        {

                            iSelected = i;
                            break;
                        }

                    }

                    int outputArr[MAX_ROADS];
                    for (int i = 0; i < MAX_ROADS; i++) {
                        outputArr[i] = -1;
                    }
                    for (int i = 0; i < MAX_ROADS; i++) {
                        outputArr[i] = arr[iSelected][i];
                    }
                    fillPathLB(hwnd, outputArr);
                    
                }
                break;
            }
        }
        break;
        }
    }
    break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
//        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void initWin2() {
    
    outputWindow.cbSize = sizeof(WNDCLASSEX);
    outputWindow.style = 0;
    outputWindow.lpfnWndProc = outputProc;
    outputWindow.cbClsExtra = 0;
    outputWindow.cbWndExtra = 0;
    outputWindow.hInstance = GetModuleHandle(NULL);
    outputWindow.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    outputWindow.hCursor = LoadCursor(NULL, IDC_ARROW);
    outputWindow.hbrBackground = (HBRUSH)COLOR_WINDOW;
    outputWindow.lpszMenuName = NULL;
    outputWindow.lpszClassName = L"Output_window";
    outputWindow.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    int foundInstance = !GetClassInfoExA(GetModuleHandle(NULL), L"Output_window", &outputWindow);
    if (foundInstance) {
        if (!RegisterClassEx(&outputWindow))
        {
            MessageBox(NULL, L"Window Registration Failed!", L"Error!",
                MB_ICONEXCLAMATION | MB_OK);
            return 0;
        }
    }
}
//void floatToStr(wchar_t str[], float flt);
// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    
    wchar_t clickedNodeId[5];
    
    switch (msg)
    {
    case WM_CREATE:
    {
        createWindowControls(hwnd);
        hwnd_NodesLB = CreateListBox(hwnd);
    }
    break;
    case WM_COMMAND:
        {
        int wmId = LOWORD(wParam);
        switch (wmId) {
            case LB_NODE:
                switch (HIWORD(wParam)) {
                    case LBN_SELCHANGE:
                    {
                        POINT p;
                        p.x = 100;
                        p.y = 150;
                        HWND ListBox = ChildWindowFromPoint(hwnd , p);
                        int count = SendMessage(ListBox, LB_GETCOUNT, 0, 0);
                        int iSelected = -1;
                        // go through the items and find the first selected one
                        for (int i = 0; i < count; i++)
                        {
                            // check if this item is selected or not..
                            if (SendMessage(ListBox, LB_GETSEL, i, 0) > 0)
                            {
                                // yes, we only want the first selected so break.
                                iSelected = i;
                                break;
                            }

                        }
                        //tostring(str, iSelected);
                        SendMessage(ListBox, LB_GETTEXT, iSelected, (LPARAM)clickedNodeId);
                        //wchar_t zero = '0';
                        int selectedNodeId = clickedNodeId[0] - L'0';
                        selectedNode = getNode(selectedNodeId);
                        
                        //populating roads pointer vector
                        //inserting into listview
                        ListView_DeleteAllItems(hwnd_listView);
                        LVITEM item;
                        item.mask = LVIF_TEXT;
                        item.cchTextMax = 6;
                        int i;
                        for (i = 0; i < MAX_ROADS; i++) {
                            if (selectedNode->roads[i] == NULL) {
                                continue;
                            }
                            roadVect[i] = selectedNode->roads[i];

                            item.iSubItem = 0;
                            wchar_t str[5];
                            tostring(str, selectedNode->id);
                            item.pszText = str;
                            item.iItem = 0;
                            ListView_InsertItem(hwnd_listView, &item);

                            item.iSubItem = 1; // zero based index of column
                            tostring(str, roadVect[i]->to);
                            item.pszText = str;
                
                            ListView_SetItem(hwnd_listView, &item);
                            item.iSubItem = 2; // zero based index of column
                            tostring(str, roadVect[i]->capacity);
                            item.pszText = str;
                            ListView_SetItem(hwnd_listView, &item);

                            item.iSubItem = 3; // zero based index of column
                            int disInt = (int)roadVect[i]->dis;
                            tostring(str, disInt);
                            item.pszText = str;
                            ListView_SetItem(hwnd_listView, &item);
                        }
                        
                           //setting node x y pos
                        wchar_t str[5];
                        tostring(str, selectedNode->x);
                        if (SetWindowText(hwnd_nodeInfoPosXEdit, str) == 0) {
                            MessageBox(NULL, L"Something went wrong!", L"Error!",
                                MB_ICONEXCLAMATION | MB_OK);
                        };

                        tostring(str, selectedNode->y);
                        if (SetWindowText(hwnd_nodeInfoPosYEdit, str) == 0) {
                            MessageBox(NULL, L"Something went wrong!", L"Error!",
                                MB_ICONEXCLAMATION | MB_OK);
                        };
                    }
                    break;
                }
                break;
            case ADD_NODE_BTN:
            {
                wchar_t str[5];
                GetWindowText(hwnd_nodeInfoPosXEdit, &str, 2);
                int Xpos = str[0] - L'0';
                GetWindowText(hwnd_nodeInfoPosYEdit, &str, 2);
                int Ypos = str[0] - L'0';
                addOperation('n', Xpos, Ypos, 0, 0, 0, 0, 0, 0, 0, 0);
                node* nodes = refreshSetup();
                wchar_t strInt[3];
                SendMessage(hwnd_NodesLB, LB_RESETCONTENT, NULL, NULL);
                for (int i = 0; i < MAX_JUNCS; i++) {
                    if (nodes[i].id == -1) continue;
                    tostring(strInt, nodes[i].id);
                    // MessageBox(NULL, )
                    SendMessageW(hwnd_NodesLB, LB_ADDSTRING, NULL, (LPARAM)strInt);
                }
            }
            break;
            case DEL_NODE_BTN:
            {
                addOperation('k', 0, 0, 0, 0, 0, selectedNode->id, NULL, 0, 0, 0);
                node* nodes = refreshSetup();
                wchar_t strInt[3];
                SendMessage(hwnd_NodesLB, LB_RESETCONTENT, NULL, NULL);
                for (int i = 0; i < MAX_JUNCS; i++) {
                    if (nodes[i].id == -1) continue;
                    tostring(strInt, nodes[i].id);
                    // MessageBox(NULL, )
                    SendMessageW(hwnd_NodesLB, LB_ADDSTRING, NULL, (LPARAM)strInt);
                }
            }
            break;
            case SAVE_CAPACITY:
            {
                if (!selectedRoad) {
                    MessageBox(NULL, L"Window Creation Failed!", L"Error!",
                        MB_ICONEXCLAMATION | MB_OK);
                }
                else {
                    wchar_t str[5];
                    GetWindowText(hwnd_capacity, &str, 2);
                    int cap = str[0] - L'0';
                    changeRoadCapacity(selectedRoad, cap);
                }
            }
            break;
            case DEL_ROAD:
            {
                if (!selectedRoad) {
                    MessageBox(NULL, L"Window Creation Failed!", L"Error!",
                        MB_ICONEXCLAMATION | MB_OK);
                }
                else {
                    //addOperation('l', NULL, NULL, NULL, NULL, NULL, NULL, selectedRoad, selectedNode->id, NULL, NULL);
                    //refreshSetup();
                    removeRoad(selectedRoad , selectedNode->id);
                }
            }
            break;
            case ADD_ROAD_BTN:
            {
                short from, to, cap;
                //from
                wchar_t str[5];
                GetWindowText(hwnd_addRoadFrom, &str, 2);
                from = str[0] - L'0';
                GetWindowText(hwnd_addRoadTo, &str, 2);
                to = str[0] - L'0';
                GetWindowText(hwnd_addRoadcapacity, &str, 2);
                cap = str[0] - L'0';
                addOperation('r', 0, 0, to, from, cap, NULL, NULL, NULL, NULL, NULL);
                refreshSetup();
            }
            break;
            case SHOW_OUTPUT:
            {
                hwnd_outputWin = CreateWindowEx(
                    WS_EX_CLIENTEDGE,
                    L"Output_window",
                    L"Output",
                    WS_OVERLAPPEDWINDOW | WS_VSCROLL,
                    CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
                    NULL, NULL, GetModuleHandle(NULL), NULL);

                if (hwnd_outputWin == NULL)
                {
                    MessageBox(NULL, L"Window Creation Failed!", L"Error!",
                        MB_ICONEXCLAMATION | MB_OK);
                    return 0;
                }
                ShowWindow(hwnd_outputWin, SW_SHOW);
                UpdateWindow(hwnd_outputWin);

            }
            break;
            case SAVE_SRC_DEST:
            {
                wchar_t str[5];
                GetWindowText(hwnd_srcEdit, &str, 2);
                int src = str[0] - L'0';
                GetWindowText(hwnd_destEdit, &str, 2);
                int dest = str[0] - L'0';
                setSourceNode(src);
                setDestNode(dest);
            }
        }
        }
        break;
    case WM_NOTIFY:
    {
        if (((LPNMHDR)lParam)->hwndFrom == hwnd_listView) {
            switch (((LPNMHDR)lParam)->code) {
            case NM_DBLCLK:
            {
                int itemint = SendMessage(hwnd_listView, LVM_GETNEXTITEM , -1, LVNI_SELECTED);
                
               
               
                

                //set road info edits
                int numRoads = 0;
                int i = 0;
                while (roadVect[i] != NULL) {
                    i++;
                    numRoads++;
                }
                int pos = numRoads - itemint - 1;
                selectedRoad = roadVect[pos];
                road* e = selectedRoad;
                wchar_t str[5];
                tostring(str, selectedRoad->capacity);
                SetWindowText(hwnd_capacity, str);
            }
            break;
            }
        }
    }
    break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    //Step 1: Registering the Window Class
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, L"Window Registration Failed!", L"Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        L"Traffic Optimizer",
        WS_OVERLAPPEDWINDOW | WS_VSCROLL,
        CW_USEDEFAULT, CW_USEDEFAULT,800, 600,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
    {
        MessageBox(NULL, L"Window Creation Failed!", L"Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    initWin2();
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop
    while (GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

void createWindowControls(HWND hwnd) {

    //Scroll bar



    HWND hwnd_title = CreateWindowW(L"static", L"Traffic Optimizer", WS_CHILD | WS_VISIBLE | SS_CENTER, 300, 20, 150, 30, hwnd, NULL, NULL, NULL);
    HWND hwnd_SimButton = CreateWindowW(L"button", L"Show output", WS_CHILD | WS_VISIBLE | SS_CENTER, 550, 20, 150, 30, hwnd, SHOW_OUTPUT, NULL, NULL);
    HWND hwnd_maxNodes = CreateWindowW(L"static", L"Max nodes: 10", WS_CHILD | WS_VISIBLE | SS_CENTER, 70, 60, 150, 50, hwnd, NULL, NULL, NULL);

    //From nodes
    HWND hwnd_nodes = CreateWindowW(L"static", L"Nodes:", WS_CHILD | WS_VISIBLE | SS_CENTER, 50, 100, 150, 20, hwnd, NULL, NULL, NULL);
    hwnd_AddNodeButton = CreateWindowW(L"button", L"AddNode", WS_CHILD | WS_VISIBLE | SS_CENTER, 550, 100, 150, 30, hwnd, ADD_NODE_BTN , NULL, NULL);

    //Entering Nodes into listbox


    // Node info
    HWND hwnd_nodeInfoTitle = CreateWindowW(L"static", L"Node Info:", WS_CHILD | WS_VISIBLE | SS_CENTER, 550, 150, 150, 30, hwnd, NULL, NULL, NULL);
    HWND hwnd_nodeInfoPos = CreateWindowW(L"static", L"Position:", WS_CHILD | WS_VISIBLE | SS_CENTER, 490, 180, 50, 20, hwnd, NULL, NULL, NULL);
    HWND hwnd_nodeInfoPosX = CreateWindowW(L"static", L"X:", WS_CHILD | WS_VISIBLE | SS_CENTER, 550, 180, 20, 20, hwnd, NULL, NULL, NULL);
    hwnd_nodeInfoPosXEdit = CreateWindowW(L"edit", L"10", WS_CHILD | WS_VISIBLE | SS_CENTER, 580, 180, 50, 20, hwnd, NULL, NULL, NULL);
    HWND hwnd_nodeInfoPosY = CreateWindowW(L"static", L"Y:", WS_CHILD | WS_VISIBLE | SS_CENTER, 660, 180, 20, 20, hwnd, NULL, NULL, NULL);
    hwnd_nodeInfoPosYEdit = CreateWindowW(L"edit", L"10", WS_CHILD | WS_VISIBLE | SS_CENTER, 700, 180, 50, 20, hwnd, NULL, NULL, NULL);
    hwnd_NodeDelButton = CreateWindowW(L"button", L"Delete Node", WS_CHILD | WS_VISIBLE | SS_CENTER, 550, 210, 150, 30, hwnd, DEL_NODE_BTN, NULL, NULL);

    //source dest control
    HWND hwnd_srcL = CreateWindowW(L"static", L"Source Node:", WS_CHILD | WS_VISIBLE | SS_CENTER, 450, 250, 150, 30, hwnd, NULL, NULL, NULL);
    int src = getSrcNode();
    wchar_t str1[5];
    tostring(str1, src);
    int dest = getDestNode();
    wchar_t str2[5];
    tostring(str2, dest);
    hwnd_srcEdit = CreateWindowW(L"edit", str1, WS_CHILD | WS_VISIBLE | SS_CENTER, 580, 250, 50, 20, hwnd, NULL, NULL, NULL);
    HWND hwnd_destL = CreateWindowW(L"static", L"Dest Node:", WS_CHILD | WS_VISIBLE | SS_CENTER, 620, 250, 150, 30, hwnd, NULL, NULL, NULL);
    hwnd_destEdit = CreateWindowW(L"edit", str2, WS_CHILD | WS_VISIBLE | SS_CENTER, 730, 250, 50, 20, hwnd, NULL, NULL, NULL);
    HWND hwnd_saveSrcDest = CreateWindowW(L"button", L"Save", WS_CHILD | WS_VISIBLE | SS_CENTER, 550, 280, 150, 20, hwnd, SAVE_SRC_DEST, NULL, NULL);
    //Roads info
    hwnd_listView = CreateWindowW(WC_LISTVIEW, NULL, WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_SORTASCENDING | LVS_SHOWSELALWAYS, 70, 350, 400, 200, hwnd, NULL, NULL, NULL);
    InitListViewColumns(hwnd_listView);

    //Roads operations

    HWND hwnd_roadCapL = CreateWindowW(L"Static", L"Capacity :", WS_VISIBLE | WS_CHILD | SS_CENTER, 520, 350, 60, 20, hwnd, NULL, NULL, NULL);
    hwnd_capacity = CreateWindowW(L"Edit", L"2", WS_VISIBLE | WS_CHILD | SS_CENTER, 580, 350, 30, 20, hwnd, NULL, NULL, NULL);
    hwnd_capacitySaveButton = CreateWindowW(L"button", L"Save", WS_CHILD | WS_VISIBLE | SS_CENTER, 620, 350, 50, 30, hwnd, SAVE_CAPACITY, NULL, NULL);
    HWND hwnd_DelRoadButtonn = CreateWindowW(L"button", L"Del", WS_CHILD | WS_VISIBLE | SS_CENTER, 700, 350, 50, 30, hwnd, DEL_ROAD, NULL, NULL);

    //Add road
    HWND hwnd_addRoadL = CreateWindowW(L"Static", L"Add road", WS_VISIBLE | WS_CHILD | SS_CENTER, 480, 400, 60, 20, hwnd, NULL, NULL, NULL);
    HWND hwnd_addRoadFromL = CreateWindowW(L"Static", L"From :", WS_VISIBLE | WS_CHILD | SS_CENTER, 480, 430, 60, 20, hwnd, NULL, NULL, NULL);
    hwnd_addRoadFrom = CreateWindowW(L"Edit", L"2", WS_VISIBLE | WS_CHILD | SS_CENTER, 520, 430, 30, 20, hwnd, NULL, NULL, NULL);
    HWND hwnd_addRoadToL = CreateWindowW(L"Static", L"TO:", WS_VISIBLE | WS_CHILD | SS_CENTER, 540, 430, 60, 20, hwnd, NULL, NULL, NULL);
    hwnd_addRoadTo = CreateWindowW(L"Edit", L"2", WS_VISIBLE | WS_CHILD | SS_CENTER, 580, 430, 30, 20, hwnd, NULL, NULL, NULL);
    HWND hwnd_addRoadCapL = CreateWindowW(L"Static", L"Capacity :", WS_VISIBLE | WS_CHILD | SS_CENTER, 610, 430, 100, 20, hwnd, NULL, NULL, NULL);
    hwnd_addRoadcapacity = CreateWindowW(L"Edit", L"2", WS_VISIBLE | WS_CHILD | SS_CENTER, 710, 430, 30, 20, hwnd, NULL, NULL, NULL);
    HWND hwnd_addRoadAddButton = CreateWindowW(L"button", L"Add", WS_CHILD | WS_VISIBLE | SS_CENTER, 600, 470, 50, 30, hwnd,  ADD_ROAD_BTN, NULL, NULL);
}


