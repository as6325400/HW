使用 heapsort 將讀取進來的邊以權重做 sort ，再用一個 DSU 去檢查所有邊的兩個端點是否已經聯通，便可求出最小生成樹

在第二次求出帶有新邊的最小生成樹時，同時紀錄每個點的 degree ， 若大於 1 則表示非葉節點，為 MST 關節點