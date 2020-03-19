#include <bits/stdc++.h>
#include<vector>
#include<iostream>
#include <boost/algorithm/string.hpp>
#include <fstream>

using namespace std; 

bool getColinearity(vector<vector<int>> x)
{
    int m = 0;
    for(int j=0;j<3;j++)
    {
        m = m + x[j][0]*(x[(j+1)%3][1]-x[(j+2)%3][1]);
    }
    if(m==0)
        return true;

    else
        return false;

}
vector<int> GenDiagPoint(int r,int c,int slope)
{
vector<int> dpoint;
if(slope==1)
{
    int r1 = r+1;
    int c1 = c-1;
    dpoint.push_back(r1);
    dpoint.push_back(c1);

    
}
else
{
    int r1 = r+1;
    int c1 = c+1;
    dpoint.push_back(r1);
    dpoint.push_back(c1);
}
return dpoint;
}

bool checkrightleft(vector<int> a,vector<int> b,vector<int> c) 
{
    return ((b[0] - a[0])*(c[1] - a[1]) - (b[1] - a[1])*(c[0] - a[0])) > 0;
}

float DistBetPoints(vector<int> x,vector<int> y)
{
return (abs(x[0]-y[0])+1);
}





vector<vector<int>> getDiagonalLine45(int r,int c,int l)
{
    vector<vector<int>> line1(2);
    int temp = r+c-1;
    int temp2= r+c-l;
    if(temp>0 && temp<=l)
    {
        line1[0].push_back(temp);
        line1[0].push_back(1);
        line1[1].push_back(1);
        line1[1].push_back(temp);
    }
    else
    {
        line1[0].push_back(temp2);
        line1[0].push_back(l);
        line1[1].push_back(l);
        line1[1].push_back(temp2);  
    }
    //for m ==1

 return line1;   

}

vector<vector<int>> getDiagonalLine135(int r,int c,int l)
{
    vector<vector<int> > line2(2);
    int temp = r-c+1;
    int temp3= r-c+l;
    if(temp>0 && temp<=l)
    {
        line2[0].push_back(temp);
        line2[0].push_back(1);
        int temp2 = c-r+l;
        line2[1].push_back(l);
        line2[1].push_back(temp2);
    }
    else
    {
        line2[0].push_back(temp3);
        line2[0].push_back(l);
        int temp4 = c-r+1;
        line2[1].push_back(1);
        line2[1].push_back(temp4);  
    }
    //for m ==1


return line2;
}


int ProcessObstacles(int r,int c,int l,vector<vector<int> > obstacles){
    vector<int> a{r,c};


    vector<int> y = GenDiagPoint(r,c,-1);
    vector<vector<int>> x = getDiagonalLine45(c,r,l);


    vector<int> pleft;
    vector<int> pright;

    int d1 = max((int)DistBetPoints(x[0],x[1])-1,0);
    if(checkrightleft(a,y,x[0]))
    {
        pleft.push_back(x[1][0]+1);
        pleft.push_back(x[1][1]-1);
        pright.push_back(x[0][0]-1);
        pright.push_back(x[0][1]+1);
    }
    else{
        pleft.push_back(x[0][0]+1);
        pleft.push_back(x[0][1]-1);
        pright.push_back(x[1][0]-1);
        pright.push_back(x[1][1]+1);

    }


    int prightdist = DistBetPoints(a,pright);
    int pleftdist = DistBetPoints(a,pleft);




    vector<vector<int>> q = getDiagonalLine135(r,c,l);
    vector<int> z = GenDiagPoint(r,c,1);

    // 0 left   1 right
    vector<int> qright;
     vector<int> qleft;
    if(checkrightleft(a,z,q[1]))
    {
        qright.push_back(q[1][0]+1);
        qright.push_back(q[1][1]+1);
        qleft.push_back(q[0][0]-1);
        qleft.push_back(q[0][1]-1);
    }
    else{
        qright.push_back(q[0][0]+1);
        qright.push_back(q[0][1]+1);
        qleft.push_back(q[1][0]-1);
        qleft.push_back(q[1][1]-1);   
    }
    
    int count = 0;
    int d2 = max((int)DistBetPoints(q[0],q[1])-1,0);
    int qrightdist = DistBetPoints(a,qright);
    int qleftdist = DistBetPoints(a,qleft);
    for(int j=0;j<obstacles.size();j++)
    {
        x.push_back(obstacles[j]);
        q.push_back(obstacles[j]);

        if(getColinearity(x) && (obstacles[j]!=a) && d1!=0){
           //for 45 degree  
            // obstacle[j]!=a make sure theat obstacle is not on position
       if(checkrightleft(a,y,obstacles[j])){
       int temp_dist = DistBetPoints(obstacles[j],a);
       if(temp_dist<prightdist){
            d1 = d1-DistBetPoints(obstacles[j],pright)+1;
            pright = obstacles[j];
            prightdist =temp_dist;
       }
   
       }
       else{
            int temp_dist = DistBetPoints(obstacles[j],a);
           if(temp_dist<pleftdist){
            d1 = d1-DistBetPoints(obstacles[j],pleft)+1;
            pleft = obstacles[j];
            pleftdist =temp_dist;
       }

       
      
    }
    }

if(getColinearity(q) && (obstacles[j]!=a) && d2!=0){
        count++;
           if(checkrightleft(a,z,obstacles[j])){
                int temp_dist = DistBetPoints(obstacles[j],a);
                if(temp_dist<qrightdist){
                    d2= d2-DistBetPoints(obstacles[j],qright)+1;
                    qright = obstacles[j];
                    qrightdist =temp_dist;
       }
   
       }
       else{
            int temp_dist = DistBetPoints(obstacles[j],a);
            if(temp_dist<qleftdist){
            d2 = d2-DistBetPoints(obstacles[j],qleft)+1;
            qleft = obstacles[j];
            qleftdist =temp_dist;
       }    
    }  
    }
    q.pop_back(); 
    x.pop_back(); 
    

}
return d1+d2;
}



int for_straight_line(int r,int c,vector<vector<int> > obstacles,int l)
{
   int count = 0; 
    int d1 = l-1;//x 180 degree
    int plefty = 0;
    int prighty = l+1;
    int d2  = l-1;// y 90 degree
    int pleftx = l+1,prightx = 0;

    for(int i=0;i<obstacles.size();i++)
    {
       int  x = obstacles[i][0];
       int  y = obstacles[i][1];
        //for m==inf
        if(x==r){
        count++;
        if(y<c){
        if((y-plefty)>0){
            d1 = d1-abs(y-plefty);
            plefty = y;
        }
        }
        else if(y>c){

            if((prighty-y)>0)
            {
                d1 = d1-abs(prighty-y);
                prighty = y;
            }

        }

        }
        //for m==0
        if(y==c){
            count++;
            if(x>r){
                if((pleftx-x)>0)
                {
                    d2 = d2-abs(pleftx-x);
                    pleftx = x;
                }
            }
            else if(x<r){
                if((x-prightx)>0)
                {
                  d2 = d2-abs(x-prightx);
                  prightx = x;   
                }
             
            }

        }
    }
return d1+d2;

}
 int output(int r,int c,int l,vector<vector<int> > obstacles)
 {
    int x =  for_straight_line(r,c,obstacles,l);
    int y = ProcessObstacles(r,c,l,obstacles);
    return x+y;

 }








main()
{

vector<vector<int>> obs;
ifstream infile;
infile.open("input3.txt");
string line;
int count =0 ;
while (getline(infile, line))
{
    count++;
    vector<string> strings;
    vector<int> res;
    boost::split(strings, line, boost::is_any_of(" "));
    int x = stoi(strings[0]);
    int y = stoi(strings[1]);
    res.push_back(x);
    res.push_back(y);
    obs.push_back(res);
}

cout<<output(48,42,10,obs)<<endl;
}