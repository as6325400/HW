# 實作新功能

## 1.計算指令數
會計算從程式開始運行到現在，總共輸入了多少次指令，不管有沒有成功執行都會被計算到，實作方法就是在 while 迴圈裡面放一個記數器，去計算迴圈進行了幾次

## 2.計算開始程式到當前的 real time
會計算從程式開始運行到現在，總共過去了多少真實時間，實作方法為在進入 main 時紀錄時間，然後在輸入 time 指令時去計算與開始時間的差值，便可獲取程式運行的真實時間

## 3.清空終端機
調用外部函數 system("cls") 清除終端機
