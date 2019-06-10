import webbrowser as web    
import time    
import os    
 
urllist=[
# "https://blog.csdn.net/qq_31027515/article/details/90613839",
# "https://blog.csdn.net/qq_31027515/article/details/90610066",
# "https://blog.csdn.net/qq_31027515/article/details/90580623",
# "https://blog.csdn.net/qq_31027515/article/details/90578548",
# "https://blog.csdn.net/qq_31027515/article/details/90578438",
# "https://blog.csdn.net/qq_31027515/article/details/90552507",
# "https://blog.csdn.net/qq_31027515/article/details/90648879",
# "https://blog.csdn.net/qq_31027515/article/details/90647002",
# "https://blog.csdn.net/qq_31027515/article/details/90675022",
# "https://blog.csdn.net/qq_31027515/article/details/90674035",
# "https://blog.csdn.net/qq_31027515/article/details/90672554",
# "https://blog.csdn.net/qq_31027515/article/details/90704371",
# "https://blog.csdn.net/qq_31027515/article/details/90704004",
# "https://blog.csdn.net/qq_31027515/article/details/90703841",
"https://blog.csdn.net/qq_31027515/article/details/90719559",
"https://blog.csdn.net/qq_31027515/article/details/90719777",
"https://blog.csdn.net/qq_31027515/article/details/90742870",
"https://blog.csdn.net/qq_31027515/article/details/90742849",
"https://blog.csdn.net/qq_31027515/article/details/90725656",
"https://blog.csdn.net/qq_31027515/article/details/90724570",
"https://blog.csdn.net/qq_31027515/article/details/90724133",

]
 
 
for j in range(0,100000):
    i=0    
    while i<1 :  
        for url in urllist:
            web.open(url)  
            i=i+1    
            time.sleep(10)  
    else: 
 
        time.sleep(5)
        os.system('taskkill /IM Firefox.exe') 
