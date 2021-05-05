

#include <avr/io.h>//K�t�phane tan�mland� tccr1b tcnt gibi kavramlar i�in

void BirKombinasyondayaz(int,int,int);//���n� birden yazd�rmak i�in fonksiyon prototipi
void YirmibesMiliSaniyeBekle(int);//25 ms beklemek i�in fonksiyon prototipi
void BirSaniyeBekle(int);//Bir saniye beklemek i�in fonksiyon prototipi
void SaliseyiYazdir(int);//Saliseyi yazd�r�rken kulland���m�z fonksiyon prototipi
void SaniyeyiYazdir(int);//Saniyeyi yazd�r�rken kulland���m�z fonksiyon prototipi
void DakikayiYazdir(int);//Dakikay� yazd�r�rken kulland���m�z fonksiyon prototipi
    
 

int main()//main fonksiyonunu tan�mlad�m
{
          DDRB=0xFF;//B portunu yani 8 den 13e kadar olan pinlerin hepsini ��k�� olarak ayarlad�k
          DDRD=0xF0;//D portunun buton pinlerini yani 2 ile 3 � giri� 4 den 8 e kadar olan display pinlerinide ��k�� olarak ayarlad�k
          TCCR1B|=((1<<CS12)|(1<<CS10));//T�mer 1 i�in prescaler de�erini 1024 olarak belirledik Buraya kadar setup k�sm�yd� �imdi loop k�sm�n� yaz�caz

while(1)//loopa girdik
{
	
  for (int dakika=9;dakika>=0;dakika--)//dakikay� dola�mas� i�in en d��ta for tan�mlad�k 9 dan ba�lay�p 0 a kadar say�cak
	{
	  for (int saniye=5;saniye>=0;saniye--)//saniyeyi dola�mas� i�in for tan�mlad�k 5 den 0 a kadar say�cak
		 {
			for (int salise=9;salise>=0;salise--)//saliseyi dola�mas� i�in for tan�mlad�k 9 dan 0 a kadar say�cak
			  {
				if ((PIND & (1 << 2))  == 0  )//1 i 2 bit sola kayd�rarak 2. pini kontrol ediyoruz bas�l� de�iilse
				  {
					if ((PIND & (1 << 3))  ==0  )//1 i 3 bit sola kayd�rarak 3. pini kontrol ediyoruz bas�l� de�ilse 
						{
						 BirKombinasyondayaz(dakika,saniye,salise);//Bu fonksiyonu �a��r fonksiyonun ne i� yapt���n� altta a��klad�m
						}
					else //i� teki ifin else inde butona bas�l� durumunu kontrol eder bas�l� ise
					{
						salise=0;//saliseyi 0 lar
						saniye=0;//saniyeyi 0 lar 
						dakika=0;//dakikay� 0 lar
					}
							
					}
					else//d��taki ifin else durumunda ise bas�l� olma durumunu kontrol eder ve bas�l� ise 
					{
					  while(1)//sonsuz d�ng� i�inde tekrar butona bas�l� olmama durumunu kontrol edicek 
					  {
						if ((PIND & (1 << 2))  ==0 )//Durdurma butonundan elimizi �ekmi�sek  yan� bas�l� de�ilse 
						{
							break;//d�ng�den ��k�cak 
					    }
					    else//e�er bas�l� ise 
						{
						 DakikayiYazdir(dakika);//O anki kombinsayon da hangi dakikada kalm��sa o dakikay� yak�cak 
						 YirmibesMiliSaniyeBekle(1);//25 ms beklicek bunu h�zl� bi �ekilde yap�cak g�zle g�r�lmemesi i�in
						 SaniyeyiYazdir(saniye);//O anki kombinasyons da hangi saniyede kalm��sa o aniyeyi yak�cak
						 YirmibesMiliSaniyeBekle(1);//25 ms beklicek bunu h�zl� bi �ekilde yap�cak yine g�zle g�r�lmemesi i�in
						 SaliseyiYazdir(salise);// O anki kombinasyon da hangi salisede kalm��sa o saliseyi yak�cak 
						 YirmibesMiliSaniyeBekle(1);//25 ms beklicek bunu h�zl� bi �ekilde yap�cak ki g�zle g�r�lmesin 25 ms nin alt�n� insan g�z� kesintisiz olarak g�r�r
						 BirSaniyeBekle(1);//ve bir saniye beklicek bu ledler bu �ekilde o kombinasyonu durdurdu�umuzda yan�p s�necek
						}
					  }
									
		
			}
					
		}
				
	}
}
		
	
}
            return 0;//mainin i�ini sonland�rd�k
}

    void BirKombinasyondayaz(int dakika ,int saniye ,int salise)//Bir kombinasyonda yazan fonksiyonumuzun i�ini tan�ml�caz
    {
	
	   for(int sayac=0;sayac<200;sayac++)//200 e kadar gitmesinin sebebi salise saniye ve dakikan�n orant�l� bi �ekilde azalmas�d�r
	     {
		   DakikayiYazdir(dakika);//bu fonksiyonun i�inde dakikayi yazd�r fonksiyonunu �a��r�yoruz bu fonksiyonun ne i� yapt���n� altta a��klad�m
		   YirmibesMiliSaniyeBekle(1);//25 MS �a��r�yoruz bunun da ne i� yapt���n� a��klad�m
		   SaniyeyiYazdir(saniye);//ayn� �ekilde saniye yi de �a��r�yoruz ne i� yapt��� altta a��kland�
		   YirmibesMiliSaniyeBekle(1);//25 ms bekliyoruz altta a��klad�m
		   SaliseyiYazdir(salise);//ve son olarak saliseyi de �a��r�yoruz altta a��klamas� bulunuyor
		   YirmibesMiliSaniyeBekle(1);//ve yine 25 ms bekliyoruz
	     }
     }

    void YirmibesMiliSaniyeBekle(int x)//25 ms bekleme yaratt���m�z fonksiyonu tan�ml�caz
    {
	   for(int sayac=1;sayac<=x;sayac++)//bu d�ng�y� �unun i�in tan�mlad�k mesela bu fonksiyonu �a��rd���m�zda bir foru 1 kere d�nd�r�rsek 25 ms bekler 40 kere d�nd�r�rsek 1 saniye bekler
	     {
		  TCNT1=65500;//65500 den 65536 ya kadar say�nca 25 ms �retir
		  while((TIFR1&(1<<TOV1))==0);//tov 1 bayra��n� s�rekli kontrol eder(polling i�lemi) 0 olunca s�rekli sayar 25 ms �retti�inde 1 olur ve d�ng�den ��kar
		  TIFR1|=(1<<TOV1);//TOV1 bayra��n� tekrar 0 layarak yeniden saymas�n� sa�l�yoruz
	     }

     }
    void BirSaniyeBekle(int x)//1saniye gecikme �retmek i�in kullanaca��m�z fonksiyon
    {
	   for(int sayac=1;sayac<=x;sayac++)//Bu da ayn� �ekilde 1 parametresiyle  �a��rd�m�zda 1sn �retir farkl� parametrelerde 1 in katlar� kadar saniye �retir
	     {
		  TCNT1=49911;//49911 den 65536 ya kadar sayd���nda 1 saniye ge�mi� olucak
		  while((TIFR1&(1<<TOV1))==0);//TOV1 bayra��n�n 1 olmas�n� bekliyoruz
		  TIFR1|=(1<<TOV1);//1 oldu�unda tekrar 0 l�yoruz ki tekrar sayabilsin
	     }
    }

   void SaliseyiYazdir(int segment)//saliseyi yazd�rmak i�in 
   {
	
	        switch(segment){//switch kontrol�n� tan�ml�yoruz
		    case 0:	//0 yakmak i�in yani 0 ise 
		    PORTD=      0x10 | // 4.pin
		                0x20 | // 5.pin
			            0x40 | // 6.pin
			            0x80 ; // 7.pin
		    PORTB=      0x01 | // 8.pin
		                0x02 | // 9.pin
			            0x20;  //salise pini bu pinler yand���nda g�stergede  0 yan�cak 
			            break;
		    case 1:	
			PORTD=      0x20 | // 5.pin
		                0x40;  // 6.pin
			PORTB=      0x20;  //salise pini bu pinler yand���nda g�stergede  1 yan�cak		
				        break;
		    case 2:	
			PORTD=      0x10 | //4.pin
			            0x20 | //5.pin
						0x80;  //7.pin
			PORTB=      0x04 | //10.pin
			            0x01 | //8.pin
						0x20;  //salise pini bu pinler yand���nda g�stergede  2 yan�cak
				        break;
		    case 3: 
		    PORTD=     0x10  | //4.pin
			           0x20  | //5.pin
					   0x40  | //6.pin
					   0x80;   //7.pin
			PORTB=     0x04  | //10.pin
			           0x20;   //salise pini bu pinler yand���nda g�stergede 3 yan�cak		
				       break;
				
		    case 4: 
			PORTD=     0x20  | //5.pin
		               0x40;   //6.pin
			PORTB=     0x04  | //10.pin
			           0x02  | //9.pin
					   0x20;   //salise pini bu pinler yand���nda g�stergede 4 yan�cak
				       break;
		    case 5: 
		    PORTD=
			           0x10  | //4.pin
					   0x40  | //6.pin
					   0x80;   //7.pin
			PORTB=     0x02  | //9.pin
			           0x04  | //10.pin
					   0x20;   //salise pini bu pinler yand���nda g�stergede 5 yan�cak 	
				       break;
		
		    case 6: 
			PORTD=     0x10  | //4.pin
			           0x40  | //6.pin
					   0x80;   //7.pin
			PORTB=
			           0x02  | //9.pin
					   0x04  | //10.pin
					   0x01  | //8.pin
					   0x20;   //salise pini bu pinler yand���nda g�stergede 6 yan�cak
				       break;
		    case 7: 
		    PORTD=     0x10  | //4.pin
			           0x20  | //5.pin
					   0x40;   //6.pin
			PORTB=     0x20;   //salise pini bu pinler yand���nda g�stergede 7 yan�cak		
				       break;
		    case 8: 
		    PORTD=     0x10  | //4.pin
			           0x20  | //5.pin
					   0x40  | //6.pin
					   0x80;   //7.pin
			PORTB=     0x01  | //8.pin
			           0x02  | //9.pin
					   0x04  | //10.pin
					   0x20;   //salise pini bu pinler yand���nda g�stergede 8 yan�cak
				       break;
		     case 9: 
			 PORTD=    0x10  | //4.pin
			           0x20  | //5.pin
					   0x40  | //6.pin
					   0x80;   //7.pin
			 PORTB=    0x02  | //9.pin
			           0x04  | //10.pin
					   0x20;   //salise pini bu pinler yand���nda g�stergede 9 yan�cak
				       break;
		
		
			}
    }

    void SaniyeyiYazdir(int segment)// bu fonksiyonda salise fonksiyonu gibi �al���r 0 1 2 3 4 5 6 7 8 9 yakmak i�in port b ye ve port d ye g�nderilen pinler ayn�d�r yaln�zca saniye biti 0x10 olarak ayarlanm��t�r
    {
	        switch(segment){
		        case 0:
				
		     PORTD=    0x10 |
		               0x20 |
		               0x40 |
		               0x80 ;
		     PORTB=    0x01 |
		               0x02 |
		               0x10;
		               break;
				
		         case 1:
			 PORTD=    0x20 |
		               0x40;
		     PORTB=    0x10;
		               break;
				
		         case 2:
			 PORTD=    0x10 |
		               0x20 |
		               0x80;
		     PORTB=    0x04 |
		               0x01 |
		               0x10;
		               break;
				
		         case 3:
		     PORTD=    0x10  |
		               0x20  |
		               0x40  |
		               0x80;
		     PORTB=    0x04  |
		               0x10;
		               break;
		        
		          case 4:
		     PORTD=    0x20  |
		               0x40;
		     PORTB=    0x04  |
		               0x02  |
		               0x10;
		               break;
				
		          case 5:
		     PORTD=
		               0x10  |
		               0x40  |
		               0x80;
		     PORTB=    0x02  |
		               0x04  |
		               0x10;
		               break;
		        
		           case 6:
		     PORTD=    0x10  |
		               0x40  |
		               0x80;
		     PORTB=    0x02  |
		               0x04  |
		               0x01  |
		               0x10;
		               break;
				
		            case 7:
		     PORTD=    0x10  |
		               0x20  |
		               0x40;
		     PORTB=    0x10;
		               break;
				
		            case 8:
		     PORTD=    0x10  |
		               0x20  |
		               0x40  |
		               0x80;
		     PORTB=    0x01  |
		               0x02  |
		               0x04  |
		               0x10;
		               break;
				
		             case 9:
		     PORTD=    0x10  |
		               0x20  |
		               0x40  |
		               0x80;
		     PORTB=    0x02  |
		               0x04  |
		               0x10;
		               break;
		        
			}
	        
    }

    void DakikayiYazdir(int segment)// bu fonksiyonda salise fonksiyonu gibi �al���r 0 1 2 3 4 5 6 7 8 9 yakmak i�in port b ye ve port d ye g�nderilen pinler ayn�d�r yaln�zca saniye biti 0x08 olarak ayarlanm��t�r
    {
		    switch(segment){
			        case 0: 
			 PORTD=    0x10  |
			           0x20  |
			           0x40  |
			           0x80 ;
			 PORTB=    0x01  |
			           0x02  |
			           0x08;
			           break;
			        
			         case 1:
			 PORTD=    0x20  |
			           0x40;
			 PORTB=    0x08;
			           break;
			        
			         case 2:
			 PORTD=    0x10  |
			           0x20  |
			           0x80;
			 PORTB=    0x04  |
			           0x01  |
			           0x08;
			           break;
			        
			         case 3:
			 PORTD=    0x10  |
			           0x20  |
			           0x40  |
			           0x80;
			 PORTB=    0x04  |
			           0x08;
			           break;
			        
			         case 4:
			 PORTD=    0x20  |
			           0x40;
			 PORTB=    0x04  |
			           0x02  |
			           0x08;
			           break;
			        
			         case 5:
			  PORTD=   0x10  |
			           0x40  |
			           0x80;
			  PORTB=   0x02  |
			           0x04  |
			           0x08;
			           break;
			        
			         case 6:
			  PORTD=   0x10  |
			           0x40  |
			           0x80;
			  PORTB=   0x02  |
			           0x04  |
			           0x01  |
			           0x08;
			           break;
			        
			         case 7:
			  PORTD=   0x10  |
			           0x20  |
			           0x40;
			  PORTB=   0x08;
			           break;
			        
			          case 8:
			  PORTD=   0x10  |
			           0x20  |
			           0x40  |
			           0x80;
			  PORTB=   0x01  |
			           0x02  |
			           0x04  |
			           0x08;
			           break;
			        
			          case 9:
			  PORTD=    0x10  |
			            0x20  |
			            0x40  |
			            0x80;
			  PORTB=    0x02  |
			            0x04  |
			            0x08;
			            break;
			        
			        
			}
    }


