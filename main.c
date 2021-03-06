#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Matrix
{
    int col_nums;
    int *cols;
    struct Matrix *next;
}Matrix;

int count_Rows(Matrix *m)
{
    int ans=0;

    // Traversing every row and incrementing the count by 1
    while(m)
    {
        ans++;
        m=m->next;
    }

    return ans;
}

bool dimensionally_similar(Matrix *m1,Matrix *m2)
{

    // If number if rows are not equal,then return false
    if(count_Rows(m1)!=count_Rows(m2))
    return false;

    // for every row,checking whether col_nums are same.If not,returning false.
    while(m1 && m2)
    {
        if(m1->col_nums!=m2->col_nums)
        return false;

        m1=m1->next;
        m2=m2->next;
    }

    // Returning True if all the previous conditions have been satisfied
    return true;
}

bool append_Row(Matrix **m,int col_count,int *arr)
{   
    // Instantiate a Matrix Row
    Matrix *instance=(Matrix *)malloc(sizeof(Matrix));  

    
    if(!instance)
    return false;

    // if the passed arg 'arr' is NULL, that means we have to take input
    if(arr==NULL){
        // Instantiating the columns as a memory block
        int *temp=(int *)calloc(sizeof(int),col_count);

        // Getting the Row Number
        int rowNum=count_Rows(*m);

        for(int i=0;i<col_count;i++)
        {
            printf("Enter mat[%d][%d]:",rowNum,i);
            scanf("%d",&(temp[i]));
        }

        instance->cols=temp;
    }
    
    else
    instance->cols=arr;

    instance->col_nums=col_count;
    instance->next=NULL;

    // If there is no Row,then just add this column to the master address
    if(*(m)==NULL)
    {
        (*m)=instance;
    }

    // Append a Row at the end
    else
    {
        Matrix *t=*m;

        while(t->next)
        t=t->next;

        t->next=instance;
    }

    return true;
}

void Print_Matrix(Matrix *m)
{
    // Traversing the Rows
    while(m)
    {
        // for every row,loop from 0 to col_nums of that,print the columns
        for(int i=0;i<m->col_nums;i++)
        {
            printf("%d ",m->cols[i]);
        }
        printf("\n");
        m=m->next;
    }
}

Matrix* add(Matrix *m1,Matrix*m2)
{

    // Requirement for adding
    if(!dimensionally_similar(m1,m2))
    return NULL;

    Matrix *instance=NULL;

    // Traversing every row of both matrix
    while(m1 && m2)
    {
        // Instantiating columns of teh new(To be Returned) Matrix
        int *temp=(int *)calloc(sizeof(int),m1->col_nums);

        // Filling the Column values
        for(int i=0;i<m1->col_nums;i++)
        {
            temp[i]=m1->cols[i]+m2->cols[i];
        }

        // Appending the Row
        append_Row(&instance,m1->col_nums,temp);

        m1=m1->next;
        m2=m2->next;
    }

    // Returning the new Matrix
    return instance;
}

Matrix* subtract(Matrix *m1,Matrix*m2)
{
       // Requirement for subtracting
    if(!dimensionally_similar(m1,m2))
    return NULL;

    Matrix *instance=NULL;

    // Traversing every row of both matrix
    while(m1 && m2)
    {
        // Instantiating columns of teh new(To be Returned) Matrix
        int *temp=(int *)calloc(sizeof(int),m1->col_nums);

        // Filling the Column values
        for(int i=0;i<m1->col_nums;i++)
        {
            temp[i]=m1->cols[i]-m2->cols[i];
        }

        
        // Appending the Row
        append_Row(&instance,m1->col_nums,temp);

        m1=m1->next;
        m2=m2->next;
    }

    // Returning the new Matrix
    return instance;
}

Matrix* get_Row(Matrix *m,int row)
{   
    printf("%d",m->col_nums);
    int i;

    // traversing until i==row and we do not reach the end of the rows
    for(i=0;m;i++)
    {
        if(i==row)
        {
            return m;
        }


        m=m->next;
    }

    // If we reach the end if the list and still not returned,then obviously the row_number os wrong for the given matrix, and so we return false

    if(!m)
    return NULL;    
}

int get(Matrix *m,int row,int col)
{
    // Getting the Specific Row
    Matrix *temp=get_Row(m,row);

    // If no Row is returned then we throw an error and exit(0)
    if(temp==NULL)
    {
        printf("\n\nRow does not exist!\n");
        exit(0);
    }

    // Traversing thorugh the columns and checking whether it is the required one
    for(int i=0;i<temp->col_nums;i++)
    {
        if(i==col)
        return temp->cols[i];
    }

    // If no columns are returned till now,then we throw an error and exit(0)
    printf("\n\nColumn does not exist in the Specific Row!\n");
    exit(0);
}


// Driver Code
int main()
{
    Matrix *mat1=NULL,*mat2=NULL;

    for(int i=0;i<4;i++)
    {
        append_Row(&mat1,i+1,NULL);
    }


    for(int i=0;i<4;i++)
    {
        append_Row(&mat2,i+1,NULL);
    }

    Print_Matrix(mat1);
    printf("\n");
    Print_Matrix(mat2);

    Matrix *te=get_Row(mat1,2);
    for(int i=0;i<te->col_nums;i++)
    {
        printf("%d ",te->cols[i]);
    }
    printf("\n");

    printf("\n\n%d is the get method result\n\n",get(mat1,2,2));
    Print_Matrix(add(mat1,mat2));
    Print_Matrix(subtract(mat1,mat2));


    return 0;   
}