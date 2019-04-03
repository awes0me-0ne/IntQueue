#include<stdio.h>
#include<stdlib.h>//malloc用
#define NODATA 0//データ無し
#define EXISTDATA 1//データあり

/*
int型データを保持するセル
キューで用いる
自己参照構造体
 */

struct intCell{
  int data;             //データ部
  struct intCell * next;//ポインタ部
};

typedef struct intCell IntCell ;
typedef IntCell* Cell_P; //セル型

struct intqueue{
  IntCell * head;//先頭ポインタ
  IntCell * tail;//末尾ポインタ
};
  typedef struct intqueue IntQueue; //キュー型

IntQueue makeQueue();//キューの作成
void enque(IntQueue *queue,int data);//データ挿入
int deque(IntQueue *queue);//データ取り出し
int isEmpty(IntQueue *queue);//空のテスト
void printQueue(IntQueue *queue);//リスト表示
void fscanToQueue(FILE*fp,IntQueue *queue);//ファイルからのデータ入力
void forward_fprint(FILE*fp,IntQueue *queue);//ファイルへ順方向に出力
Cell_P makeCell(int n);//セル作成

int main(){
  //キューの動作
  IntQueue queue;
  IntQueue *q_p;
  FILE *fp_in,*fp_out;

  queue=makeQueue();//キュー生成
  q_p=&queue;
  printQueue(q_p);
  
  fp_in=fopen("IntData","r");
  fscanToQueue(fp_in,q_p);
  fclose(fp_in);

  printf("キューを表示します。\n");
  printQueue(q_p);

  printf("ファイルへ順に出力します。\n");
  fp_out=fopen("IntForward","w");
  forward_fprint(fp_out,q_p);//ファイルへ順に出力
  fclose(fp_out);

  printf("キューを表示します。\n");
  printQueue(q_p);

  return 0;
}

IntQueue makeQueue(){
  IntQueue queue;
  queue.head=NULL;
  queue.tail=NULL;
  return queue;
}

int isEmpty(IntQueue *queue){
  if(queue->head==NULL){
    return NODATA;
  }else{
    return EXISTDATA;
  }
}

Cell_P makeCell(int n){
  Cell_P new =(Cell_P)malloc(sizeof(IntCell));
  new->data=n;
  return new;
}

void enque(IntQueue *queue,int data){
  Cell_P new_cell=makeCell(data);
  if(isEmpty(queue)==NODATA){
  queue->head=new_cell;
  queue->tail=new_cell;
  }else{
    queue->tail->next=new_cell;
    queue->tail=new_cell;
  }
  return;
}

int deque(IntQueue * queue){
  int idata;
  Cell_P remove;
  if(queue->head!=queue->tail){
    remove=queue->head;
    idata=remove->data;
    queue->head=queue->head->next;
    free(remove);
    return idata;
  }else if(queue->head==queue->tail){//最後の一個の削除
    remove=queue->head;
    idata=remove->data;
    queue->head=NULL;
    queue->tail=NULL;
    free(remove);
    return idata;
  }else{
    printf("No data\n");
    return -1;
  }
}

void printQueue(IntQueue *queue){
  Cell_P p=queue->head;
  if(queue->head==NULL){
    printf("()\n");
  }else{
    printf("(");
  while(p!=queue->tail){
    printf("%3d,",p->data);
    p=p->next;
  }
  printf("%3d,",p->data);
  printf(")\n");
  }
  return ;
}

void fscanToQueue(FILE *fp,IntQueue *queue){
  int idata;
  while(fscanf(fp,"%d",&idata)!=EOF){
    enque(queue,idata);
  }
  return;
}
void forward_fprint(FILE * fp,IntQueue *queue){
  int idata;
  while(isEmpty(queue)==EXISTDATA){
    idata=deque(queue);
    fprintf(fp,"%3d",idata);
  }
  return ;
}

