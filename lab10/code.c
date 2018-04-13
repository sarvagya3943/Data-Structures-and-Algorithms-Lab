#include "ex3.h"
#include <string.h>
#define ROOT "http://172.24.16.12/wiki/index.html"
#define MAX_DEPTH 10
#define SIZE 200

CURL *curl_handle;
char *vis[SIZE];
int vis_sz;

typedef struct node node;
struct node {
	int vis_idx,depth;
};

node queue[SIZE];

node make_node(int a,int b) {
	node n=(node)malloc(sizeof(node));
	n->vis_idx=a;
	n->depth=b;
	return *n;
}

int get_idx(const char *x) {

	int i;
	for(i=0;i<vis_sz;i++) if(strcmp(x,vis[i])==0) return -1; 
	
	if(vis_sz==SIZE) return -1;
	sprintf(vis[vis_sz],"%s",x);

	return vis_sz++;
}

void bfs(const char *start) {
	int lo=0,hi=0;
	char name[20],buf[200];
	
	queue[hi++]=make_node(get_idx(start),0);
	
	while(lo<hi && hi<SIZE)  {
		node cur=queue[lo++];
		int idx=cur.vis_idx;
		int depth=cur.depth;
		
		sprintf(name,"%d.html",idx);
		save_file(name,vis[idx],curl_handle);
		
		if(depth==MAX_DEPTH) continue;
		
		//get new links and save if not visited
		FILE *fptr=fopen(name,"r");
		while(!feof(fptr)) {
		}
	}			
}

int main() {
	curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();
    vis_sz=0;
	bfs(ROOT);
    curl_easy_cleanup(curl_handle);
	return 0;
}
