#include <stdio.h>
#include <algorithm>
#include <queue>
#include <memory.h>
using namespace std;

#define NN 333
#define beyond(x, y) (x<0 || y<0 || x>=width || y>=height)

char raw_name[100]="map1.raw";
int height=200,width=250;
unsigned char buffer[NN*NN];


// read map with size(W*H)
void inline read(const char* filename, int W, int H){
	FILE* fp=fopen(filename,"rb");
	fread(buffer, W, H , fp);
}

// input the map file name and the size of map
void input(){
	scanf("%s %d %d",raw_name,&height,&width);	
}

int dx[]={0, 1, 0, -1};
int dy[]={-1, 0, 1, 0};

int dis[NN][NN];
int flag[NN][NN];

typedef pair <int, int> pii;
priority_queue <pii, vector <pii>, greater <pii> > pq;

// calulate the shortest path from cell(0, 0) to all others
void solve(){
	
	memset(dis, 0x3f, sizeof(dis));
	dis[0][0]=buffer[0];
	
	pq.push(pii(dis[0][0], 0));
	while(!pq.empty()){
		pii tmp=pq.top();
		pq.pop();
		int y=tmp.second/width;
		int x=tmp.second%width;
		
		// consider four cells which are reachable from the cuurent cell(x, y)
		for(int i=0; i<4; i++){
			int xx=x+dx[i];
			int yy=y+dy[i];
			
			// determine that the cell(xx, yy) is in the map
			if(beyond(xx, yy)) continue;
			if(dis[yy][xx]>dis[y][x]+buffer[yy*width+xx]){
				dis[yy][xx]=dis[y][x]+buffer[yy*width+xx];
				pq.push(pii(dis[yy][xx], yy*width+xx));
				flag[yy][xx]=i+1;
			}
		}
	}
}

int main(){
 	//input();
	read(raw_name,width,height);
	/*
	freopen("out.txt","w",stdout);
	for(int i=0; i<height; i++){
		for(int j=0; j<width; j++){
			printf("%d ", buffer[i*width+j]); 
		}
		puts("");
	}
	fclose(stdout);
	*/
	solve();
	
	freopen("ShortestPath.txt","w",stdout);
	for(int i=0; i<height; i++){
		for(int j=0; j<width; j++){
			printf("%d ", dis[i][j]); //50,100,150,200
		}
		puts("");
	}
	fclose(stdout);
	
	freopen("path.raw","wb",stdout);
	for(int i=0; i<height; i++){
		for(int j=0; j<width; j++){
			printf("%c", 50*flag[i][j]); //50,100,150,200
		}
	}
	fclose(stdout);

	
	return 0;		
}
