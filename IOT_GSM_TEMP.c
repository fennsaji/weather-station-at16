#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>
#include<mylib/iot.h>
#include<mylib/adc.h>

unsigned int x=0;

void wait(){
	char x=0;
	while(1){
		x=usart_rec();
		if(x=='O'){
			x=usart_rec();
			if(x=='K'){
				_delay_ms(150);
				return;
			}
		}
	}
}

void msg(){
	DDRA=0X00;
	adc_init();
	usart_init();
	unsigned char msgf[]="AT+CMGF=1\r\n",msgs[]="AT+CMGS=\"8882345398\"\r\n",msgt1[]="Temperature=",msgt2[]="*C";
	x=adc_read(1);
	x=x*4;
	x=x/10;
	usart_string(msgf);
	_delay_ms(300);
	usart_string(msgs);
	_delay_ms(300);
	usart_string(msgt1);
	usart_number(x);
	usart_string(msgt2);
	_delay_ms(300);
	usart_send(0x1A);	
}
void server(){
	 usart_init();
	 unsigned char gprs[]="AT+CIPCSGP=1,\"INTERNET\"\r\n",gprs2g[]="AT+CIPMUX=0\r\n",shut[]="AT+CIPSHUT\r\n",start[]="AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n",send[]="AT+CIPSEND\r\n",data[]="GET https://api.thingspeak.com/update?api_key=TBTD8A8CX1DESGNT&field1=0";
	 usart_string(gprs2g);
	// _delay_ms(300);
	 wait();
	 usart_string(gprs);
	 //_delay_ms(300);
	 wait();
	 usart_string(start);
	 //_delay_ms(5000);
	 wait();
	 usart_string(send);
	 _delay_ms(1000);
	 usart_string(data);
	 usart_number(x);
	 //_delay_ms(300);
	 usart_send(0x1A);
	 usart_string(shut);
	 _delay_ms(300);
}

void main(){ 
	 //unsigned char call[]="ATD8882345398;\r\n", hang[]="ATH\r\n";
	// unsigned char msgf[]="AT+CMGF=1\r\n",msgs[]="AT+CMGS=\"8882345398\"\r\n",msgt[]="jai mata di...";
	// usart_init();
	 for(;;)
	 {
	  //calling 
	/*  iot_string(call);
	  _delay_ms(10000);_delay_ms(10000);_delay_ms(10000);
	  iot_string(hang);
	  _delay_ms(10000);
	*/

	 //msging 
	/* iot_string(msgf);
	  _delay_ms(300);
	  iot_string(msgs);
	  _delay_ms(300);
	  iot_string(msgt);
	  _delay_ms(300);
	  usart_send(0x1A);
	  _delay_ms(10000);
	*/ 

	//testing of number fun

	/* iot_string("Temperature: ");
	  usart_number(50);
	  iot_string(" *C");
	  iot_string("\r\n");
	  _delay_ms(10000);
	*/

	//temperature data via msg and server

//	  msg();
	  server();
	  _delay_ms(10000);
	  _delay_ms(10000);	
	 }
}

