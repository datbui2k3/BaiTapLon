#include<iostream>
#include<fstream>
#include<stack>
#include<queue>
#include<stdio.h>
#include<conio.h>
#include<vector>
#include <string>
#define infinity 9999
#define MAX 20
#define MAX 100
#define TRUE 1
#define FALSE  0
using namespace std;

int n,m , minl , connect ; // so dinh cua do thi.
int dau[1001], cuoi[1001], w[1001];//Mang chua dinh dau va cuoi cua do thi
int daut[100], cuoit[100], father[100];
int matrix[1001][1001];//ma tran ke luu tru
bool visited[1001];//xac nhan da duyet
// tim duong di
int forward_point[1001];
//doc ma tra
void Init()
{
    ifstream file("fileinput.txt", ios::in);//doc file text
    file >> n;//doc dinh , de luu vao dem
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            file >> matrix[i][j];
        }
        visited[i] = false;// CHUA THANG
        forward_point[i] = 0;
    }
}
// Doc ma File Cac cah
void intFile(){
	 freopen("input.txt", "r",stdin);
     cin>>n>>m;
     cout<<"So dinh do thi: "<< n <<endl;
     cout<<"So canh do thi:" << m <<endl;
//Nhap danh sach ke
 for (int i = 1; i <= m; i++){

  cin>>dau[i]>>cuoi[i]>>w[i];
 }
}
// DFS
void DFS(int u)
{
    cout << "DFS(" << u << "): ";// In ra lo trinh
    stack<int> st; // chuyen doi tu chux sang so
    st.push(u);//dau dinh vao stack
    visited[u] = true;// dc tham roi
    cout << u << " ";// in dinh ra
    //Lap cho den khi stack rong
    while(!st.empty())
    {
        int v = st.top();//lay dinh dau stack
        //tim duong di
        int s = st.top();
        // chung tim duong di và DFS
        st.pop();
        for(int t = 1; t <= n; t++)
        {
            if(visited[t] == false && matrix[v][t] == 1);//kiem tra dinh thang hay chua va ke voi no
            if(visited[t] == false && matrix[s][t] == 1)
            {
                cout << t << " ";// di tham
                forward_point[t] = s;
                visited[t] = true;//da tham thanh true
                st.push(v);//dua vao ngan xep
				//tim duong di
                st.push(s);
                //
                st.push(t);//dua vao ngan xep
                //khi push ra phai dua lai vao
                break;
                //Chu y : Khi thang dinh xong thi se break ra ngoai va lap lai xet thang dinh khach
            }
        }
    }
}

// BFS
void BFS(int u)
{
    cout << "BFS(" << u << "): ";//IN RA LO TRINH
    queue<int> Q;//CHYEN DOI DINH
    Q.push(u);//DAU U VAO QUEUE
    visited[u] = true;//THANG DINH U
    while(!Q.empty())
    {
        int s = Q.front();//LAY DINH DAU TIEN
        cout << s << " ";// DAY DINH RA MAN HINH
        Q.pop();// LAY DINH DAU TIEN RA KHOI QUEUE
        for(int t = 1; t <= n; t++)
        {
            if(visited[t] == false && matrix[s][t] == 1) //kiem tra dinh thang hay chua va ke voi no
            {
                Q.push(t);//CHO T VAO OUEUE
                visited[t] = true;//DA THANG
            }
        }
    }
}

// Cai dat thuat toan Dijkstra
void PrintPath(int s, int e)
{
    if(forward_point[e] == 0)
        cout << "Khong Co Con Duong Nao Giua " << s << " Va " << e << endl;
    else
    {
        cout << "Duong Dan: ";
        cout << e ;
        int u = forward_point[e];
        while(u != s)
        {
            cout << " <- " << u;
            u = forward_point[u];
        }
        cout << " <- " << s;
    }
}

// Cai dat thuat toan Krusal 
void Heap(int First, int Last){

 int a, k, t1, t2, t3;

 a = First;

 while (a <= (Last / 2)){

  if ((2 * a) < Last && w[2 * a + 1] < w[2 * a])

   k = 2 * a + 1;

  else

   k = 2 * a;

  if (w[k] < w[a]){

   t1 = dau[a];

   t2 = cuoi[a];

   t3 = w[a];

   dau[a] = dau[k];

   cuoi[a] = cuoi[k];

   w[a] = w[k];

   dau[k] = t1;

   cuoi[k] = t2;

   w[k] = t3;

   a = k;

  }

  else a = Last;

 }

}

int Find(int i){

 int tro = i;

 while (father[tro] > 0)

  tro = father[tro];

 return(tro);

}

void Union(int i, int a){

 int x = father[i] + father[a];

 if (father[i] > father[a]) {

  father[i] = a;

  father[a] = x;

 }

 else {

  father[a] = i;

  father[i] = x;

 }

}
void Krusal(void){

 int last, u, v, r1, r2, ncanh, ndinh;

 for (int i = 1; i <= n; i++)

  father[i] = -1;

 // Su dung thuat toan vun dong de sap xep cac canh cua do thi theo thu tu khong giam cua do canh 

 for (int i = m / 2; i > 0; i--)

  Heap(i, m);



 last = m; ncanh = 0; ndinh = 0; minl = 0; connect = TRUE;

 //Lua chon canh bo xung vao cay khung

 while (ndinh < n - 1 && ncanh < m){

  ncanh = ncanh + 1;

  u = dau[1];

  v = cuoi[1];

  //tim goc cua phan hach 1 

  r1 = Find(u);

   //tim goc cua phan hach 2 

  r2 = Find(v);

  if (r1 != r2) {//neu hai goc khac nhau thi canh co the them vao dc do thi

   ndinh = ndinh + 1;

   Union(r1, r2);

   daut[ndinh] = u;

   cuoit[ndinh] = v;

   minl = minl + w[1];

  }

  dau[1] = dau[last];

  cuoi[1] = cuoi[last];

  w[1] = w[last];

  last = last - 1;

  Heap(1, last);

 }

 if (ndinh != n - 1) connect = FALSE;

}

void Result(void){

 cout<<"Do dai cay khung nho nhat:"<< minl<<endl;

 cout<<"Cac canh cua cay khung nho nhat:"<<endl;

 for (int i = 1; i < n; i++)

  cout<< daut[i]<<" "<<cuoit[i]<<endl;

}

//end
int menu(){


    int control;
    do{
    	cout << "Cai Dat Thuat Toan Trong Do Thi" << endl;
        cout << "Hay chon menu sau:" << endl;
        cout << "Nhap 1: Cai Dat Thuat Toan Tim Kiem Chieu Sau (DFS)" << endl;
        cout << "Nhap 2: Cai Dat Thuat Toan Tim Kiem Theo Chieu Rong (BFS)" << endl;
        cout << "Nhap 3: Cai Dat Thuat Toan Dijkstra" << endl;
        cout << "Nhap 4: Cai Dat Thuat Toan Krusal" << endl;
        cout << "Nhap 0: De Thoat Khoi Ung Dung" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "Ban Chon" <<endl;
    
    cin >> control;
   
	  switch (control){
        case 1:
            cout << "Cai Dat Thuat Toan Tim Kiem Chieu Sau (DFS)" << endl;
            // Code Cai Dat Thuat Toan Tim Kiem Chieu Sau (DFS)
            //DFS
            int s; // dinh bat dau.
            Init();
            cout << "Chon dinh bat dau DFS: ";
            cin >> s;//mhap s vao
            DFS(s);//goi vaf nhap s vao
            cout << "\n";
        break;
        case 2:
            cout << "Cai Dat Thuat Toan Tim Kiem Theo Chieu Rong (BFS)" << endl;
            // Code Cai Dat Thuat Toan Tim Kiem Theo Chieu Rong (BFS)
            //BFS
            int u; // DINH BAT DAU
            Init();
            cout << "Chon dinh bat dau BFS : ";
            cin >> u;//NHAP U VAO
            BFS(u);// GAI VA NHAP U VAO
            cout << "\n";
        break;
        case 3:
            cout << "Cai Dat Thuat Toan Dijkstra" << endl;
            // Code Cai Dat Thuat Toan Dijkstra
            int e;
            Init();
            cout <<"Nhap Diem Dau Tien: ";
            cin >> s;
            cout << "Nhap Diem Cuoi Cung: ";
            cin >> e;
            DFS(s);
            PrintPath(s, e);
            cout <<"\n";
        break;
        case 4:
            cout << "Cai Dat Thuat Toan Krusal" << endl;
            // Code Cai Dat Thuat Toan Krusal

            intFile();
        
            Krusal();
            Result();
            getch();
          return 2;
        break;	
        case 0 :
        	 cout << "Ban da thoat chuong trinh" << endl;
        	 break;
		
        default :
            cout << "Ban chon sai chuong trinh" << endl;
            break;
           
    };
	
  }while (control);
}

int main() {
	menu();
	return 0;
}
  


