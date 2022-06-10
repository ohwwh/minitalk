Minitalk

Summary
두 개의 UNIX signal만을 이용하여 메시지를 주고 받는 두 개의 프로세스를 작성해야 한다. 
비유하자면, 청기와 백기를 드는 것 만으로 메시지를 보낼 수 있는 방법을 궁리해야 한다.

Specifications
(과제 pdf)
실행 파일의 이름은 client와 server여야 한다
파일 하나당 하나의 전역변수만 사용할 수 있다
server는 실행되면서 자신의 PID를 표시해야 하며, 복수의 client로 부터 계속 메시지를 받을 수 있어야 한다.
예컨데, 한 client에게 받은 메시지를 표시 한 후 종료되어서는 안된다.
client는 메시지를 보낼 server의 PID와, 문자열 형태의 메시지를 인자로 받는다. 메시지를 보낸 후, client는 종료된다.
server의 메세지 처리는 '충분히' 빨라야 한다. 예컨데 100자의 메시지를 보내는데 1초 이상이 소요된다면, 문제가 있다!
오직 SIGUSR1 과 SIGUSR2 두 개의 신호만 사용할 수 있다.
(Bonus)
server는, 모든 signal마다 client가 보낸 signal을 수신했다는 signal을 client에게 보내야 한다.
유니코드 문자의 송신을 지원해야 한다.

How to use
make all 실행
server 폴더에서 ./server 실행
client 폴더에서 ./client [server의 PID] [보내고 싶은 메시지]의 형태로 실행

What to learn?
UNIX signal, signal handler
비동기적인 함수 실행의 원리
비트연산자
유니코드와 UTF-8 인코딩
TCP와 3 way handshake
운영체제와 프로세스의 signal 처리방식, PCB구조, Process간 context switching
유닉스 시스템 프로세스, Swapper, init process, idle process

Features

