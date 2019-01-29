# Algorithm
Algorithms, Fall 2018 @NTUEE

1. 使用之程式語言：< C++ >

2. 使用之編譯器：< GNU g++ >

3. 檔案壓縮方式: 7-Zip

4. 各檔案說明：
	 
>b05901182\src\insertionSort.cpp: Insertion sort的cpp檔  
>b05901182\src\mergeSort.cpp: Merge sort的cpp檔    
>b05901182\src\heapSort.cpp: Heap sort的cpp檔  
>b05901182\src\quickSort.cpp: Quick sort的cpp檔  
>b05901182\src\parser.cpp : 做文字檔的前處理  
>b05901182\src\parser.h : 做文字檔的前處理  
>b05901182\readme.txt : 操作此份作業的說明檔  
>b05901182\report.docx : 此份作業的報告  

5. 編譯方式說明：        	
   
>(1) Insertion sort : 在terminal輸入 g++ insertionSort.cpp parser.h -o [executable_file_name]  
>(2) Merge sort     : 在terminal輸入 g++ mergeSort.cpp parser.h -o [executable_file_name]  
>(3) Heap sort      : 在terminal輸入 g++ heapSort.cpp parser.h -o [executable_file_name]  
>(4) Quick sort     : 在terminal輸入 g++ quickSort.cpp parser.h -o [executable_file_name]  

6. 執行、使用方式說明：

>(1) Insertion sort : 在terminal輸入 ./[executable_file_name] [input_file_name] [output_file_name]  
>(2) Merge sort     : 在terminal輸入 ./[executable_file_name] [input_file_name] [output_file_name]  
>(3) Heap sort      : 在terminal輸入 ./[executable_file_name] [input_file_name] [output_file_name]  
>(4) Quick sort     : 在terminal輸入 ./[executable_file_name] [input_file_name] [output_file_name]  

7. 執行結果說明（說明執行結果的觀看方法，及解釋各項數據等）：

>在terminal中只會輸出執行的時間，有關sort的output結果需要到[executable_file_name]查看  
>例如: 在terminal編譯好cpp檔後輸入 ./quickSort case1.dat out1  
>terminal則會輸出  The execution spends 0.013 seconds  
>在生成的out1檔裡則會顯示  

    1362
    A 576
    A 1078
    Alcarnus 130
    ......
