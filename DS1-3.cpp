#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>

using namespace std;

#define MAX_SIZE 100

typedef enum {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3
    } Direction;

typedef struct {
    int x, y;
    int blocked;
    int portal_x, portal_y;
    } Room;

struct Node {
    int x, y;
    int distance;
    vector<pair<int, int>> path;//紀錄路徑
};
void findpath(char maze[MAX_SIZE][MAX_SIZE], Room rooms[MAX_SIZE][MAX_SIZE], int rows, int cols, ofstream& outFile){
    int start_x = -1, start_y = -1;
    int goal_x = -1, goal_y = -1;

    // 尋找起點和終點
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] == 'S') {
                start_x = i;
                start_y = j;
            } else if (maze[i][j] == 'G') {
                goal_x = i;
                goal_y = j;
            }
        }
    }

    if (start_x == -1 || goal_x == -1) {
        outFile << "NO PATH" << endl;
        return;
    }

    //最短路徑搜尋
    bool visited[MAX_SIZE][MAX_SIZE];
    memset(visited, false, sizeof(visited));

    queue<Node> mark;//儲存有分岔路的節點
    Node start = {start_x, start_y, 0, {{start_y, start_x}}};//y,x
    mark.push(start);
    visited[start_x][start_y] = true;
    
    bool found = false;

    

    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};
    while (!mark.empty() &&!found) {
        Node current = mark.front();
        mark.pop();

        
        if (current.x == goal_x && current.y == goal_y) {
            found = true;

            outFile << current.distance+1 << ", ";//路徑字串

            for (size_t i = 0; i < current.path.size(); i++) {//y,x
                outFile << "(" << current.path[i].second << "," << current.path[i].first << ")";
                if (i < current.path.size() - 1) {
                    outFile << " -> ";
                }
            }
            outFile << endl;
            break;
        }

        if(maze[current.x][current.y] == 'P') {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    // 如果是另一個傳送門且不是當前位置
                    if (maze[i][j] == 'P' && (i != current.x || j != current.y)) {
                        if (!visited[i][j]) {
                            visited[i][j] = true;

                            Node portalNode = current;
                            portalNode.x = i;
                            portalNode.y = j;
                            portalNode.distance++;
                            portalNode.path.push_back({j, i});  // 注意：在路徑中存入 (y,x) 順序

                            mark.push(portalNode);
                        }
                        break;  // 找到對應的傳送門後就跳出
                    }
                }
            }
        }

        // 探索四個方向：上、右、下、左
        for (int dir = 0; dir < 4; dir++) {
            int nx = current.x + dx[dir];
            int ny = current.y + dy[dir];

            // 檢查是否走過且沒有#
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && !visited[nx][ny] && maze[nx][ny] != '#') {
                visited[nx][ny] = true;

                Node nextNode = current;
                nextNode.x = nx;
                nextNode.y = ny;
                nextNode.distance++;
                nextNode.path.push_back({ny, nx});  

                mark.push(nextNode);
            }
        }
    }

    if (!found) {
        outFile << "NO PATH" << endl;
    }
}


int main(){
        ifstream inFile("testcase3.txt");
        ofstream outFile("output3.txt");

        int rows;
        int cols;
        int start[MAX_SIZE][MAX_SIZE];
        int portal[MAX_SIZE][MAX_SIZE];
    inFile >> rows >> cols;
    char maze[MAX_SIZE][MAX_SIZE];
    inFile.ignore();
    for (int i = 0; i < rows; i++) {
        string line;
        getline(inFile, line);
        for (int j = 0; j < line.length() && j < cols; j++) {
            maze[i][j] = line[j];
        }
    }

  
    Room rooms[MAX_SIZE][MAX_SIZE];//初始化ROOM
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            rooms[i][j].x = j;
            rooms[i][j].y = i;
            rooms[i][j].blocked = (maze[i][j] == '#');
            rooms[i][j].portal_x = -1;
            rooms[i][j].portal_y = -1;
        }
    }

    int num_operations;
    inFile >> num_operations;
    for(int i = 0; i < num_operations; i++){
        string line;
        inFile>>line;
        if(line=="block"){
            int x, y;
            inFile>>y>>x;

            if(y >= 0 && y < rows && x >= 0 && x < cols && maze[y][x] == '.'){
                maze[y][x]='#';
                rooms[y][x].blocked = true;
            }else {
            outFile << "INVALID OPERATION" << endl;
            }
        } else if(line=="unblock"){
            int x, y;
            inFile>>y>>x;//y為直行x為橫列
            if (y >= 0 && y < rows && x >= 0 && x < cols && maze[y][x] == '#' && !(y == 0 || x == 0 || y == rows-1 || x == cols-1)) {
                maze[y][x] = '.';
            } else {
                outFile << "INVALID OPERATION" << endl;
            }
        } else if(line=="portal"){
            int y1, x1, y2, x2;
            inFile >> y1 >> x1 >> y2 >> x2;

            if (y1 >= 0 && y1 < rows && x1 >= 0 && x1 < cols && y2 >= 0 && y2 < rows && x2 >= 0 && x2 < cols && maze[y1][x1] == '.' && maze[y2][x2] == '.' )  {
                // 設置新的傳送門
                maze[y1][x1] = 'P';
                maze[y2][x2] = 'P';
            }else {
                outFile << "INVALID OPERATION" << endl;
            }
        } else if(line=="path"){
            findpath(maze, rooms, rows, cols, outFile);
        } else if(line=="print"){
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    outFile << maze[i][j];
                }
                outFile << endl;
            }
        }
    }
        inFile.close();
        outFile.close();
    return 0;
}
