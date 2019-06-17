#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class simplex{
private:
    //float **A, **B;
    vector<vector<float>> A;
    vector<vector<float>> B;
    int row_, column_;
    bool target;
    pair<int, int> pivot_coord;
public:
    simplex(int row, int column, bool tar) : row_(row), column_(column), target(tar){
        A.resize(row_);
        for(int i = 0; i < row; i++)
            A[i].resize(column_);
        B.resize(row_);
        for(int i = 0; i < row; i++)
            B[i].resize(column_);
    }

    void init(){
        cout << "Enter free terms\n";
        for(int i = 0; i < row_; i++)
             cin >> A[i][0];
        cout << "Enter coefficients\n";
        for(int i = 0; i < row_; i++)
             for(int j = 1; j < column_; j++)
                cin >> A[i][j];
        int count = 0;
        for(int j = 1; j < column_; j++){
            if(A[0][j] != 0)
                A[0][j] = -1 * A[0][j];
            if(A[0][j] == 0)
                count++;
        }
        if(count == column_-1){
            cout << "No solutions, since objective function is empty\n";
            exit(0);
        }
        bool flag;
        for(int i = 1; i < row_; i++){
            cout << i << " condition is more or less? (1/0) ";
            cin >> flag;
            for(int j = 1; j < column_; j++)
                if((flag == 1) && (A[i][j] != 0))
                    A[i][j] = -1 * A[i][j];
            if((flag == 0) && (A[i][0] != 0))
                    A[i][0] = -1 * A[i][0];
        }
    }

    void print(vector<vector<float>> C){
        for(int i = 0; i < row_; i++){
            for(int j = 0; j < column_; j++){
                if(i == pivot_coord.first && j == pivot_coord.second && i != 0 && j != 0){
                    cout << fixed;
                    cout.precision(2);
                    cout << "\033[31m" << setw(5) << C[i][j] << "\033[37m" << " ";
                    continue;
                }
                cout << fixed;
                cout.precision(2);
                cout << setw(5) << C[i][j] << " ";
            }
            cout << endl;
        }
    }

    void find_resolving_elem_index(int type){
        float razr, minimum;
        minimum = 0;
        if(type == 0){
            for(int i = 0; i < row_; i++){
                if((A[i][0] < 0) && (i != 0)){
                    for(int j=0;j < column_;j++){
                        if((A[i][j] < 0) && (j != 0)){
                            for(int m = 0; m < row_; m++){
                                if((A[m][j] != 0) && (m != 0)){
                                    razr = A[m][0] / A[m][j];
                                    if(razr > 0){
                                    if((minimum == 0) || (razr < minimum)){
                                        minimum  = razr;
                                        pivot_coord.first = i;
                                        pivot_coord.second = j;
                                    }
                                }
                            }
                        }
                        if ((pivot_coord.first != 0) && (pivot_coord.second != 0)){
                            return;
                        } else {
                            cout << "The system of equations is not compatible "
                                    "with the inequalities arising from the "
                                    "non-negativity of the variables. Solution doesn't exist\n";
                            exit(0);
                        }
                        }
                    }
                }
            }
        }
        if(type == 1){
            for(int j=0; j < column_; j++){
                if((A[0][j] > 0) && (j != 0)){
                    for(int i = 0; i < row_; i++){
                        if((A[i][j] > 0) && (i != 0)){
                            if(A[i][j] > 0){
                                razr = A[i][0] / A[i][j];
                                if((minimum == 0) || (razr < minimum)){
                                    minimum  = razr;
                                    pivot_coord.first = i;
                                    pivot_coord.second = j;
                                }
                            }
                        }
                    }
                    if ((pivot_coord.first != 0) && (pivot_coord.second != 0)){
                        return;
                    } else {
                        cout << "The objective function decreases indefinitely "
                                "under any set of basic variables. "
                                "Optimal solution doesn't exist\n";
                        exit(0);
                    }
                }
            }
        }
        if(type == 2){
            for(int j = 0; j < column_; j++){
                if((A[0][j] < 0) && (j != 0)){
                    for(int i = 0; i < row_; i++){
                        if((A[i][j] > 0) && (i != 0)){
                            if (A[i][j] > 0){
                                razr = A[i][0] / A[i][j];
                                if((minimum == 0) || (razr < minimum)){
                                    minimum  = razr;
                                    pivot_coord.first = i;
                                    pivot_coord.second = j;
                                }
                            }
                        }
                    }
                    if ((pivot_coord.first != 0) && (pivot_coord.second != 0)){
                        return;
                    } else {
                        cout << "The objective function increases indefinitely "
                                "under any set of basic variables. "
                                "Optimal solution doesn't exist\n";
                        exit(0);
                    }
                }
            }
        }
        pivot_coord.first   = 0;
        pivot_coord.second  = 0;
    }

    string change_basis(){
        for(int i = 0; i < row_; i++)
            for(int j = 0; j < column_; j++){
                if((i != pivot_coord.first) && (j != pivot_coord.second))
                    B[i][j] = A[pivot_coord.first][j] * (A[i][pivot_coord.second] *
                            (-1) / A[pivot_coord.first][pivot_coord.second]);
                if(i == pivot_coord.first)
                    B[i][j] = A[i][j] * (1 /A[pivot_coord.first][pivot_coord.second]);
                if(j == pivot_coord.second)
                    B[i][j] = A[i][j] * (-1) /A[pivot_coord.first][pivot_coord.second];
                if((i == pivot_coord.first) && (j == pivot_coord.second))
                    B[i][j] = 1 / A[pivot_coord.first][pivot_coord.second];
            }
        for(int i = 0; i < row_; i++)
            for(int j = 0; j < column_; j++){
                if((i != pivot_coord.first) || (j != pivot_coord.second))
                    A[i][j] = A[i][j] + B[i][j];
                if((i == pivot_coord.first)||(j == pivot_coord.second))
                    A[i][j] = B[i][j];
            }
        return "y" + to_string(pivot_coord.first) + "<->" + "x" + to_string(pivot_coord.second);
    }

    void simplex_method(){
        init();
        cout << "Original table\n";
        find_resolving_elem_index(0);
        print(A);
        int step = 1;
        while(pivot_coord.first != 0 && pivot_coord.second !=0){
            string message(change_basis());
            cout<<"Step: "<< step << endl;
            find_resolving_elem_index(0);
            cout << "Temp table: " << endl;
            print(B);
            cout << message << " Result: " << endl;
            print(A);
            step++;
        }

        cout << "Reference solution exist\n";

        if(target == 0){
            find_resolving_elem_index(1);
            cout<<"Find optimal solution if exists" << endl;
            cout<<"Table:"<<endl;
            print(A);
            while(pivot_coord.first != 0 && pivot_coord.second !=0){
                string message(change_basis());
                cout<<"Step: "<< step << endl;
                find_resolving_elem_index(1);
                cout << "Temp table: " << endl;
                print(B);
                cout << message << " Result: " << endl;
                print(A);
                step++;
            }
        }
        if(target == 1){
            find_resolving_elem_index(2);
            cout<<"Find optimal solution if exists" << endl;
            cout<<"Table:"<<endl;
            print(A);
            while(pivot_coord.first != 0 && pivot_coord.second !=0){
                string message(change_basis());
                cout<<"Step: "<< step << endl;
                find_resolving_elem_index(2);
                cout << "Temp table: " << endl;
                print(B);
                cout << message << " Result: " << endl;
                print(A);
                step++;
            }
        }
        cout << "Optimal solution exist:" << endl;
        if(target == 0)
            cout << "L\u2098\u2097\u2099 = " << A[0][0] << endl;
        if(target == 1)
            cout << "L\u2098\u2090\u2093 = " << A[0][0] << endl;
    }
};

int main()
{
    int target, var_quantity, con_quantity;
    cout << "Max or min(1/0) ";
    cin >> target;
    cout << "Variables quantity: ";
    cin >> var_quantity;
    cout << "Conditions quantity: ";
    cin >> con_quantity;
    simplex gg(con_quantity + 1, var_quantity + 1, target);
    gg.simplex_method();
    //gg.init();
    //gg.print();
    //gg.find_resolving_elem_index(0);
    return 0;
}
