#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <math.h>
#include <stdlib.h>

#define max_size 10000000
long long int q_and_alpha[2];
long long int arr[max_size];//contains all prime factors of n(repetition allowed)
long long int distinct_pfactors[max_size];
long long int u[max_size];
long long int v[max_size];
long long int prime[max_size];
//this is the fastest possible algorithm to count primes upto given n
//this program calculates all primes upto given n in least possible time
//this program is faster than seive in calculating primes upto 10^9
long long int gen_primes(long long int n)
{
  long long int i,j,k;
  long long int temp;
  long long int p,q,r;
  long long int m,x;
  p = sqrt(n);
  i = (1 + p)/6;//no of iteration
  k = ((n+1)/6) + 1;//bitset no:
  for(r=1;r<=k;r++)
  {
    u[r] = 1;
    v[r] = 1;
  }


  for(j=1;j<=i;j++)
  {

    if(v[j]==1)
    {
      m = 6*j-1;
      temp = m - j;
      q = 1;
      u[n] = 0;
      while((j+q*m)<=(k-1) && (temp+q*m)<=(k-1))
      {
        v[j+q*m]=0;
        u[temp+q*m] = 0;
        q++;
      }

      if((j+q*m)<=(k-1))
        v[j+q*m] = 0;
      if((temp+q*m)<=(k-1))
        u[temp+q*m] = 0;
    }
    if(u[j]==1)
    {
      m = 6*j + 1;
      temp = m - j;
      v[temp] = 0;
      q=1;
      while((j+q*m) <=(k-1) && (temp+q*m)<=(k-1))
      {
        u[j+q*m]=0;
        v[temp+q*m] = 0;
        q++;
      }
      if((j+q*m)<=(k-1))
        u[j+q*m] = 0;
      if((temp+q*m)<=(k-1))
        v[temp+q*m] = 0;
    }


  }
  x = 0;
  x++;
  prime[x] = 2;
  if(n!=2)
  {
    x++;
    prime[x] = 3;
  }
  for(r=1;r<=k-1;r++)
  {
    if(v[r]==1 && (6*r-1)<=n)
    {

      x++;
      prime[x] = 6*r - 1;
    }
    if(u[r]==1 && (6*r+1)<=n && r!=4)
    {
      x++;
      prime[x] = 6*r + 1;
    }
  }

  return x;
}

//this program will compute prime factors of given input n in O(sqrt(n))
//here we can give 19 digit input number as here we put all prime factors
//of n in arr[] of size 10^8(a 19 digit number cant have this much factors)
long long int fact(long long int n)
{
  long long int i,j,k;
  j = 0;
  for(i=2;i*i<=n;i++)
  {

    while(n%i==0)
    {
      j++;
      arr[j] = i;
      n = n/i;
    }
  }
  if(n!=1)
  {
    j++;
    arr[j] = n;
  }

  return j; //returning last index of arr
}


long random_at_most(long range) {
  unsigned long
    // max <= RAND_MAX < ULONG_MAX, so this is okay.
    num_bins = (unsigned long) range + 1,
             num_rand = (unsigned long) RAND_MAX + 1,
             bin_size = num_rand / num_bins,
             defect   = num_rand % num_bins;

  long x;
  do {
    x = random();
  }
  // This is carefully written not to overflow
  while (num_rand - defect <= (unsigned long)x);

  // Truncated division is intentional
  return x/bin_size;
}


long random_number(long min, long max){

  return min+random_at_most(max-min);

}


long long int power_mod(long long int a, long long int b, long long int m)
{
  long long int temp,r;
  temp = a%m;
  r = 1;
  if(b==0 && m==1)
    return 0;
  else{


    while(b>0)
    {
      if(b%2==1)
      {
        r = r*temp;
        r = r%m;
      }
      b = b/2;
      temp = (temp*temp)%m;
    }

    return r;
  }
}


void global_public_elements(){
  //find the least primitive root of randomly generated prime q
  long long int n=max_size;
  long long int num_primes=gen_primes(n);
  long long int rand_num=random_number(2,num_primes);
  long long int q = prime[rand_num];
  long long int phi_q = q-1;
  long long int num_pfactors = fact(phi_q);
  long long int a,i,j,k;
  long long int x=0;
  long long int alpha;
  long long int count;
  for(i=1;i<=num_pfactors;i++){

    //arr[j]
    //printf("%lld ",arr[i]);
    for(j=1;j<=i;j++){

      if (arr[i]==arr[j]){

        break;
      }
      if(i==j){
        x=x+1;
        distinct_pfactors[x]=arr[i];

      }
    }
  }

  for(a=2;a<=q-1;a++){
    count=0;
    for(i=1;i<=x;i++){
      if(power_mod(a,phi_q/distinct_pfactors[i],q)!=1){
        count++;
      }
      else{
        break;
      }
    }
    if (count==x){
      alpha=a;
      break;
    }
  }


  q_and_alpha[1]=q;
  q_and_alpha[2]=alpha;
}
long long int privatekey(long long int p){
  //p is prime , according to theory: private key(X) < p
  long long int X;
  X = random_number(2,p-1);
  return X;
}
long long int publickeyA(long long int Xa){

  long long int Ya;
  Ya = power_mod(q_and_alpha[2],Xa,q_and_alpha[1]);
  return Ya;
}

long long int publickeyB(long long int Xb){

  long long int Yb;
  Yb = power_mod(q_and_alpha[2],Xb,q_and_alpha[1]);
  return Yb;
}
//#define Port_Num 8081
//Create a Socket for server communication
short SocketCreate(void)
{
  short hSocket;
  //printf("Create the socket\n");
  hSocket = socket(AF_INET, SOCK_STREAM, 0);
  return hSocket;
}

//try to connect with server
int SocketConnect(int hSocket,int Port_Num)
{
  int iRetval=-1;
  int ServerPort = Port_Num;
  struct sockaddr_in remote={0};
  remote.sin_addr.s_addr = inet_addr("127.0.0.1"); //Local Host
  remote.sin_family = AF_INET;
  remote.sin_port = htons(ServerPort);
  iRetval = connect(hSocket , (struct sockaddr *)&remote , sizeof(struct sockaddr_in));
  return iRetval;
}

// Send the data to the server and set the timeout of 20 seconds
int SocketSend(int hSocket,char* Rqst,int lenRqst)
{
  int shortRetval = -1;
  struct timeval tv;
  tv.tv_sec = 20;
  tv.tv_usec = 0;
  if(setsockopt(hSocket, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv,sizeof(tv)) < 0)
  {
    printf("Time Out\n");
    return -1;
  }
  shortRetval = send(hSocket , Rqst , lenRqst , 0);
  return shortRetval;
}

//receive the data from the server
int SocketReceive(int hSocket,char* Rsp,int RvcSize)
{
  int shortRetval = -1;
  struct timeval tv;
  tv.tv_sec = 20;
  tv.tv_usec = 0;
  if(setsockopt(hSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(tv)) < 0)
  {
    printf("Time Out\n");
    return -1;
  }
  shortRetval = recv(hSocket, Rsp , RvcSize , 0);
  //printf("Response %s\n",Rsp);
  return shortRetval;
}


void EncryptionAlgorithm (char *plaintext, char *ciphertext, long long int key);
void DecryptionAlgorithm (char *ciphertext, char *recoveredtext, long long int key);
long long int Encoding(char c );
char Decoding(long long int i);


//main driver program
int main(int argc , char *argv[])
{
  int hSocket, read_size;
  struct sockaddr_in server;
  char plaintext[1024]={0};
  char ciphertext_AB[1024]={0};
  char ciphertext_BA[1024]={0};
  char recoveredtext[1024]={0};
  long long int public_global_elements[3]={0};
  long long int Kab,Xa,Ya,Yb;
  long long int len,key;
  int Port_Num;
  int create_socket_flag=0,send_status,return_status;
  global_public_elements();

  printf("Value of q:- %lld\n",q_and_alpha[1]);
  printf("Value of alpha:- %lld\n",q_and_alpha[2]);

  Xa = privatekey(q_and_alpha[1]);
  printf("Private key of A:- %lld\n",Xa);
  Ya = publickeyA(Xa);
  printf("Public key of A:- %lld\n",Ya);

  public_global_elements[0]=q_and_alpha[1];
  public_global_elements[1]=q_and_alpha[2];
  public_global_elements[2]=Ya;

  Port_Num=8080;

//while(1)
  //{

    //Create socket
    hSocket = SocketCreate();
    if(hSocket == -1)
    {
      printf("Could not create socket.\n");
      return 1;
    }
    printf("Socket is created.\n");

    //Connect to remote server
    if (SocketConnect(hSocket,Port_Num) < 0)
    {
      perror("Unable to establish connection");
      return 1;
    }

    printf("Sucessfully conected with server.\n");
    printf("Port of server:- %d\n",Port_Num);
    send_status = send(hSocket,public_global_elements,sizeof(public_global_elements),0);

    if (send_status>0)
    {
        printf("Sending public key tuple is successfull.\n");

    }
    return_status = recv(hSocket,&Yb,sizeof(Yb),0);
    if (return_status>0){
        printf("Public key of B recieved.\n");
        printf("Public key of B:- %lld\n",Yb);

        Kab = power_mod(Yb,Xa,q_and_alpha[1]);
        printf("K_AB is:- %lld\n",Kab);

        key = Kab%67;
      }

while(1)
{
    if (create_socket_flag==1)
    {
           hSocket = SocketCreate();

        if(hSocket == -1)
        {
          printf("Could not create socket.\n");
          return 1;
        }
        printf("Socket is created.\n");

        if (SocketConnect(hSocket,Port_Num) < 0)
        {
          perror("Unable to establish the connection");
          return 1;
        }
        printf("Sucessfully conected with server.\n");

    }

    printf("Enter the Message to be sent to B:: ");
    gets(plaintext);
    len = strlen(plaintext);

    printf("Plaintext to be sent to B:: \n");
    puts(plaintext);
    printf("Key used in encryption:: %lld\n", key);

    EncryptionAlgorithm (plaintext, ciphertext_AB, key);
    printf("Ciphertext sent to B:: \n");
    puts(ciphertext_AB);

    //send_status = SocketSend(hSocket , ciphertext , strlen(ciphertext));
    send_status = send(hSocket,ciphertext_AB,strlen(ciphertext_AB),0);
    //printf("%d\n",send_status);
    //return_status = SocketReceive(hSocket , recoveredtext ,500);
     if (send_status>0)
    {
      printf("Sending Cipertext to B is successfull.\n");
    }
    return_status = recv(hSocket,ciphertext_BA,1024,0);
    //printf("%d\n",return_status);

    if (return_status>0){
      printf("Waiting to recieve ciphertext from B....\n");
      printf("Ciphertext received from B:: \n");
      puts(ciphertext_BA);
      DecryptionAlgorithm(ciphertext_BA,recoveredtext,key);
      printf("Msg decrypted by A:: \n");
      puts(recoveredtext);

      }


    close(hSocket);
    //shutdown(hSocket,0);
    //shutdown(hSocket,1);
    //shutdown(hSocket,2);
    create_socket_flag=1;
}

  return 0;
}

void EncryptionAlgorithm (char *plaintext, char *ciphertext, long long int key)
{
  /* Technique used:: c = E (p) = (p + key) mod 67 */
  long long int p, c;
  long long int i, len;
  len = strlen (plaintext);
  for (i=0; i< len; i++) {
    p = Encoding (plaintext[i]);
    c = ( p + key) % 67;
    ciphertext[i] = Decoding ( c );

  }
  ciphertext[i] =  '\0';
}

/* Function to decrypt a ciphertext using Caeser Cipher */
void DecryptionAlgorithm (char *ciphertext, char *recoveredtext, long long int key)
{
  /* Technique used:: p = E (c) = (c - key) mod 67 */
  long long int p, c;
  long long int i, len;
  len = strlen (ciphertext);
  for (i=0; i< len; i++) {
    c = Encoding (ciphertext[i]);
    p = ( c - key) % 67;
    if (p < 0 ) {
      p = - p;
      p = ((67-1) * p) % 67;
    }
    recoveredtext[i] = Decoding ( p );
    if ( p == 66)
      recoveredtext[i] = 33;
  }
  recoveredtext[i] =  '\0';

}

/* Function to encode a character to its numerical equivalent */
long long int Encoding(char c )
{
  /* [space]=0,A = 0, B = 1, ...., ! = 66*/
  long long int p;
  /* char: A, B, ..., Z */
  if ( c >= 65 && c <= 90 )
    p = c - 65 + 1;

  /* char: a, b, ..., z */
  else if ( c >= 97 && c <= 122 )
    p = c - 97 + 40;

  /* char: 0,1,2,3,4...9 */
  else if (c>=48 && c<=57)
    p=c-48 + 30;

  else if ( c == 32 ) /* blank char */
    p = c-32;

  else if (c==44) /* , */
    p=c-17;

  else if(c==46) /* . */
    p=c-18;

  else if (c==63) /*  ?   */
    p=c-34;

  else if(c==33) /*  ! */
    p=c+33;

  else {
    printf("Encoding:: Error in plaintext: character outside english alphabets!!! \n");
    exit(0);
  }

  return p;

}

/* Function to decode a numerical value to its corresponding character */
char Decoding(long long int i)
{
  char c;

  if ( i >= 1 && i<= 26)
    c = 'A' + i -1;

  else if (i>=40 && i<=65)
    c = 'a' + i - 40;

  else if(i>=30 && i<=39)
    c = '0'+ i - 30;

  else if ( i == 0 )
    c = 32;

  else if (i==27)
    c=44;

  else if(i==28)
    c=46;

  else if(i==29)
    c=63;

  else if(i==66)
    c=33;

  else {
    printf("Decoding:: Error in ciphertext: character outside english alphabets!!! (i= %lld, c = %c) \n", i, c);
    exit(0);
  }
  return c;
}
