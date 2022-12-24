#include <windows.h>
#include "service.h"
#include <CommCtrl.h>

void tostring(wchar_t str[], int num)
{
    int i, rem, len = 0, n;

    n = num;
    
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

BOOL InitListViewColumns(HWND hWndListView)
{
    LVCOLUMN lvc;
    memset(&lvc, 0, sizeof(lvc));
    lvc.cx = 80;
    lvc.fmt = LVCFMT_RIGHT;
    // Initialize the LVCOLUMN structure.
    // The mask specifies that the format, width, text,
    // and subitem members of the structure are valid.
    lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvc.pszText = L"From";
    SendMessage(hWndListView, LVM_INSERTCOLUMN, 0, (LPARAM)&lvc); // Insert/Show the coloum
    lvc.pszText = L"To";
    SendMessage(hWndListView, LVM_INSERTCOLUMN, 1, (LPARAM)&lvc); // Insert/Show the coloum
    lvc.pszText = L"Capacity";
    SendMessage(hWndListView, LVM_INSERTCOLUMN, 2, (LPARAM)&lvc); // Insert/Show the coloum
    lvc.pszText = L"Distance";
    SendMessage(hWndListView, LVM_INSERTCOLUMN, 3, (LPARAM)&lvc); // Insert/Show the coloum
    return TRUE;
}
void createWindowControls(HWND hwnd) {

    //Scroll bar

    
    wchar_t strInt[3];
    HWND hwnd_title = CreateWindowW(L"static", L"Traffic Optimizer", WS_CHILD | WS_VISIBLE | SS_CENTER, 300, 20, 150, 30, hwnd, NULL, NULL, NULL);
    HWND hwnd_SimButton = CreateWindowW(L"button", L"Show output", WS_CHILD | WS_VISIBLE | SS_CENTER, 550, 20, 150, 30, hwnd, NULL, NULL, NULL);
    HWND hwnd_maxNodes = CreateWindowW(L"static", L"Max nodes: 10", WS_CHILD | WS_VISIBLE | SS_CENTER, 70, 60, 150, 50, hwnd, NULL, NULL, NULL);

    //From nodes
    HWND hwnd_nodes = CreateWindowW(L"static", L"Nodes:", WS_CHILD | WS_VISIBLE | SS_CENTER, 50, 100, 150, 20, hwnd, NULL, NULL, NULL);
    HWND hwnd_AddNodeButton = CreateWindowW(L"button", L"AddNode", WS_CHILD | WS_VISIBLE | SS_CENTER, 550, 100, 150, 30, hwnd, NULL, NULL, NULL);

    //Entering Nodes into listbox
    node* nodes = initialSetup();
    HWND hwnd_NodesLB = CreateWindowW(L"ListBox" , NULL , WS_VISIBLE | WS_CHILD | LBS_STANDARD | LBS_NOTIFY , 70 , 130 , 400 , 200 , hwnd , NULL , NULL , NULL);
    for (int i = 0; i < MAX_JUNCS; i++) {
        if (nodes[i].id == -1) continue;
        tostring(strInt, nodes[i].id);
        SendMessageW(hwnd_NodesLB, LB_ADDSTRING, NULL, (LPARAM) strInt);
    }

    // Node info
    HWND hwnd_nodeInfoTitle = CreateWindowW(L"static", L"Node Info:", WS_CHILD | WS_VISIBLE | SS_CENTER, 550, 150, 150, 30, hwnd, NULL, NULL, NULL);
    HWND hwnd_nodeInfoPos = CreateWindowW(L"static", L"Position:", WS_CHILD | WS_VISIBLE | SS_CENTER, 490, 180, 50, 20, hwnd, NULL, NULL, NULL);
    HWND hwnd_nodeInfoPosX = CreateWindowW(L"static", L"X:", WS_CHILD | WS_VISIBLE | SS_CENTER, 550, 180, 20, 20, hwnd, NULL, NULL, NULL);
    HWND hwnd_nodeInfoPosXEdit = CreateWindowW(L"edit", L"10", WS_CHILD | WS_VISIBLE | SS_CENTER, 580, 180, 50, 20, hwnd, NULL, NULL, NULL);
    HWND hwnd_nodeInfoPosY = CreateWindowW(L"static", L"Y:", WS_CHILD | WS_VISIBLE | SS_CENTER, 660, 180, 20, 20, hwnd, NULL, NULL, NULL);
    HWND hwnd_nodeInfoPosYEdit = CreateWindowW(L"edit", L"10", WS_CHILD | WS_VISIBLE | SS_CENTER, 700, 180, 50, 20, hwnd, NULL, NULL, NULL);
    HWND hwnd_NodeSaveButton = CreateWindowW(L"button", L"Save", WS_CHILD | WS_VISIBLE | SS_CENTER, 550, 220, 150, 30, hwnd, NULL, NULL, NULL);
    HWND hwnd_NodeDelButton = CreateWindowW(L"button", L"Delete Node", WS_CHILD | WS_VISIBLE | SS_CENTER, 550, 260, 150, 30, hwnd, NULL, NULL, NULL);

    //Roads info
    HWND hwnd_listView = CreateWindow(WC_LISTVIEW, NULL, WS_VISIBLE | WS_CHILD | LVS_REPORT| LVS_EX_AUTOSIZECOLUMNS, 70, 350, 400, 200, hwnd, NULL, NULL, NULL);
    InitListViewColumns(hwnd_listView);

    //Roads operations

    HWND hwnd_roadCapL = CreateWindowW(L"Static", L"Capacity :", WS_VISIBLE | WS_CHILD | SS_CENTER, 520, 350, 60, 20, hwnd ,  NULL, NULL, NULL);
    HWND hwnd_capacity = CreateWindowW(L"Edit", L"2", WS_VISIBLE | WS_CHILD | SS_CENTER, 580, 350, 30, 20, hwnd, NULL, NULL, NULL);
    HWND hwnd_capacitySaveButton = CreateWindowW(L"button", L"Save", WS_CHILD | WS_VISIBLE | SS_CENTER, 620, 350, 50, 30, hwnd, NULL, NULL, NULL);
    HWND hwnd_DelRoadButtonn = CreateWindowW(L"button", L"Del", WS_CHILD | WS_VISIBLE | SS_CENTER, 700, 350, 50, 30, hwnd, NULL, NULL, NULL);

    //Add road
    HWND hwnd_addRoadL = CreateWindowW(L"Static", L"Add road", WS_VISIBLE | WS_CHILD | SS_CENTER, 480, 400, 60, 20, hwnd, NULL, NULL, NULL);
    HWND hwnd_addRoadFromL = CreateWindowW(L"Static", L"From :", WS_VISIBLE | WS_CHILD | SS_CENTER, 480, 430, 60, 20, hwnd, NULL, NULL, NULL);
    HWND hwnd_addRoadFrom = CreateWindowW(L"Edit", L"2", WS_VISIBLE | WS_CHILD | SS_CENTER, 520, 430, 30, 20, hwnd, NULL, NULL, NULL);
    HWND hwnd_addRoadToL = CreateWindowW(L"Static", L"TO:", WS_VISIBLE | WS_CHILD | SS_CENTER, 540, 430, 60, 20, hwnd, NULL, NULL, NULL);
    HWND hwnd_addRoadTo = CreateWindowW(L"Edit", L"2", WS_VISIBLE | WS_CHILD | SS_CENTER, 580, 430, 30, 20, hwnd, NULL, NULL, NULL);
    HWND hwnd_addRoadCapL = CreateWindowW(L"Static", L"Capacity :", WS_VISIBLE | WS_CHILD | SS_CENTER, 610, 430, 100, 20, hwnd, NULL, NULL, NULL);
    HWND hwnd_addRoadcapacity = CreateWindowW(L"Edit", L"2", WS_VISIBLE | WS_CHILD | SS_CENTER, 710, 430, 30, 20, hwnd, NULL, NULL, NULL);
    HWND hwnd_addRoadAddButton = CreateWindowW(L"button", L"Add", WS_CHILD | WS_VISIBLE | SS_CENTER, 600, 470, 50, 30, hwnd, NULL, NULL, NULL);
}