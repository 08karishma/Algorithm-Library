//https://leetcode.com/problems/range-sum-query-2d-mutable/submissions/

class NumMatrix {
public:
    vector<vector<int>> tree;
    int R, C;
    vector<vector<int>> arr;
    
    void buildInnerTree(int innerNode, int colStart, int colEnd, int outerNode, int rowStart, int rowEnd){
        if(colStart == colEnd){
            if(rowStart == rowEnd){
                tree[outerNode][innerNode] = arr[rowStart][colStart];
            }
            else{
                tree[outerNode][innerNode] = tree[2*outerNode][innerNode] + tree[2*outerNode+1][innerNode];
            }
            return;
        }
        int colMid = (colStart + colEnd)/2;
        buildInnerTree(2*innerNode, colStart, colMid, outerNode, rowStart, rowEnd);
        buildInnerTree(2*innerNode+1, colMid+1, colEnd, outerNode, rowStart, rowEnd);
        tree[outerNode][innerNode] = tree[outerNode][2*innerNode] + tree[outerNode][2*innerNode + 1];        
    }
    
    void buildOuterTree(int outerNode, int rowStart, int rowEnd){
        if(rowStart != rowEnd){
            int rowMid = (rowStart + rowEnd)/2;
            buildOuterTree(outerNode*2, rowStart, rowMid);
            buildOuterTree(outerNode*2 + 1, rowMid+1, rowEnd);
        }
        buildInnerTree(1, 0, C-1, outerNode, rowStart, rowEnd);
    }
    
    void updateInnerTree(int innerNode, int colStart, int colEnd, int outerNode, int rowStart, int rowEnd, 
                         int colIndex, int value)
    {
        if(colStart>colIndex || colEnd<colIndex){
            return;
        }
        if(colStart == colEnd){
            if(rowStart == rowEnd){
                tree[outerNode][innerNode] = value;
                arr[rowStart][colStart] = value;
            }
            else{
                tree[outerNode][innerNode] = tree[2*outerNode][innerNode] + tree[2*outerNode+1][innerNode];
            }
            return;
        }
        int mid = (colStart + colEnd)/2;
        updateInnerTree(2*innerNode, colStart, mid, outerNode, rowStart, rowEnd, colIndex, value);
        updateInnerTree(2*innerNode+1, mid+1, colEnd, outerNode, rowStart, rowEnd, colIndex, value);
        tree[outerNode][innerNode] = tree[outerNode][2*innerNode] + tree[outerNode][2*innerNode+1];
    }
    
    void updateOuterTree(int outerNode, int rowStart, int rowEnd, int rowIndex, int colIndex, int value){
        if(rowStart>rowIndex || rowEnd<rowIndex){
            return;
        }       
        if(rowStart != rowEnd){
            int mid = (rowStart + rowEnd)/2;
            updateOuterTree(2*outerNode, rowStart, mid, rowIndex, colIndex, value);
            updateOuterTree(2*outerNode+1, mid+1, rowEnd, rowIndex, colIndex, value);
        }
        updateInnerTree(1, 0, C-1, outerNode, rowStart, rowEnd, colIndex, value);
    }
    
    int queryInnerTree(int innerNode, int colStart, int colEnd, int outerNode, int colLeft, int colRight){
        if(colStart>colRight || colEnd<colLeft){
            return 0;
        }
        if(colStart>=colLeft && colEnd<=colRight){
            return tree[outerNode][innerNode];
        }
       int colMid = (colStart + colEnd)/2;
       return queryInnerTree(2*innerNode, colStart, colMid, outerNode, colLeft, colRight)
               +
               queryInnerTree(2*innerNode+1, colMid+1, colEnd, outerNode, colLeft, colRight);
    }
    
    int queryOuterTree(int outerNode, int rowStart, int rowEnd, int rowLeft, int rowRight, 
                       int colLeft, int colRight)
    {
        if(rowStart>rowRight || rowEnd<rowLeft){
            return 0;
        }
        if(rowStart>=rowLeft && rowEnd<=rowRight){
            return queryInnerTree(1, 0, C-1, outerNode, colLeft, colRight);
        }
        int rowMid = (rowStart + rowEnd)/2;
        return queryOuterTree(2*outerNode, rowStart, rowMid, rowLeft, rowRight, colLeft, colRight)
            +
                queryOuterTree(2*outerNode+1, rowMid+1, rowEnd, rowLeft, rowRight, colLeft, colRight);
    }
    
    NumMatrix(vector<vector<int>>& matrix) {
        R = matrix.size();
        if(R == 0) return;
        C = matrix[0].size();
        
        tree.resize(4*R);
        for(int i=0; i<4*R; i++){
            tree[i].resize(4*C);
        }
        arr = matrix;
        buildOuterTree(1, 0, R-1);
    }
    
    void update(int row, int col, int val) {
        updateOuterTree(1, 0, R-1, row, col, val);
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return queryOuterTree(1, 0, R-1, row1, row2, col1, col2);
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * obj->update(row,col,val);
 * int param_2 = obj->sumRegion(row1,col1,row2,col2);
 */
