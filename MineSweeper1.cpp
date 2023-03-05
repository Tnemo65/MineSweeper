#include<bits/stdc++.h>
using namespace std;
const int MAX = 100;
const int MAX_MINES = 100;
int m, n, k; //Hàng, cột, số mìn
int bang[MAX][MAX];
bool trangThai[MAX][MAX];

void taoMin(){
    srand(time(NULL));
    int dem = 0;
    while(dem < k){
        //Phải để trong vòng while
        //Mỗi vòng thì tạo ra (x, y) khác nhau
        int x = rand() % m;
        int y = rand() % n;        
        //Nếu ô mang giá trị -1 rồi thì bỏ qua
        if(bang[x][y] != -1){
            bang[x][y] = -1;
            dem ++;
        }
    }
}

void inBang(){
    cout << "  ";
    for(int i = 0; i < m; i++){
        cout << i << " ";
    }
    cout << endl;
    for(int i = 0; i < m; i++){
        cout << i << " ";
        for(int j = 0; j < n; j++){
            //Nếu ô đã được mở
            if(trangThai[i][j] == true){
                //Nếu ô đó chứa bom
                if(bang[i][j] == -1){
                    //In ra *
                    cout << "* ";
                }
                //Nếu không chứa bom thì in ra giá trị của ô là 0
                else{
                    cout << bang[i][j] << " ";
                }
            }
            //Nếu chưa mở ô thì in .
            else{
                cout << ". ";
            }
        }
        cout << endl;
    }
}

int demMin(int x, int y){
    int dem = 0;
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            //Nếu chạy đến chính nó thì bỏ qua
            if( i == 0 && j == 0){
                continue;
            }                   //ví dụ chạy x = y = 1
            int hang = x + i;   // 00  01  02
            int cot = y + j;    // 10 (11) 12
                                // 20  21  22
            if(hang >= 0 && hang <= m && cot >= 0 && cot <= m && bang[hang][cot] == -1){
                dem++;
            }
        }
    }
    return dem;
}

int main(){
    cout << "Rule: Enter 0 < m, n, k < 10" << endl;
    cout << "Enter the size of the minefield (m, n) and the number of mines: " << endl;
    do{
        cin >> m >> n >> k;
    }
    while(m <= 0 || n <= 0 || m > 10 || n > 10 || k <= 0 );
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            //Gán giá trị bảng = 0
            bang[i][j] = 0;
            //Trạng thái đều là false <=> chưa mở ô
            trangThai[i][j] = false;
        }
    }
    taoMin();
    bool lose = false;
    while(lose == false){
        inBang();
        cout << endl;

        cout << "Please enter your present place (x, y): ";
        int x, y;
        cin >> x >> y;
        //Trường hợp nhập tọa độ không hợp lí
        if(x < 0 || x >= m || y < 0 || y >= n){
            cout << "The place is invalid, please retry!"<< endl;
            continue;
        }
        //Nếu chọn trúng ô đã được mở trước đó
        if(trangThai[x][y] == true){
            cout << "The place was opened, please retry!" << endl;
            continue;
        }
        //Mở ô
        trangThai[x][y] = true;
        //Nếu đúng ô có bom -> thua
        if(bang[x][y] == -1){
            cout << "YOU'RE DEAD!" << endl;
            cout << "The final board is: " << endl;
            inBang();
            lose = true;
        }
        else{
            //Nếu x, y thỏa mãn điều kiện thì gán bang[x][y]=số mìn
            //Không in luôn mà đầu vòng while sau mới in
            bang[x][y] = demMin(x,y);
            //Đếm ô chưa mở
            int demOChuaMo = 0;
            for(int  i = 0; i < m; i++){
                for(int j = 0; j < n; j++){
                    if(trangThai[i][j] == false){
                        demOChuaMo ++;
                    }
                }
            }
            //Nếu số ô chưa mở = số bom -> win
            if(demOChuaMo == k){
                cout <<"YOU'RE WIN!" << endl;
                cout << "The final board is: " << endl;
                inBang();
                cout << endl;
                lose = true;
            }
        }
    }
}