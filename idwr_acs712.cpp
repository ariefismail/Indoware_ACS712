#include "idwr_acs712.h"

int titik_nol;

idwr_acs712::idwr_acs712(uint8_t tipe_sensor_acs712,float vref){
	switch(tipe_sensor_acs712){
			case 5: //acs 5A
				skala_acs = 5.45; // 1000/185
			break;
			
			case 20: //acs 20A
				skala_acs = 10; // 1000/100
			break;
			
			case 30: //acs30A
				skala_acs = 15.15; // 1000/66
			break;
			
			default:
				skala_acs = 5.45;
			break;
	}
	tegangan_referensi=vref;
}

//ambil nilai adc pada pin dan konversikan langung dalam bentuk arus AMPERE
float idwr_acs712::arus_dc(uint8_t pin_adc){
	return (skala_acs*((float)analogRead(pin_adc)-(float)titik_nol)*tegangan_referensi/resolusi_adc);
	}
	
float idwr_acs712::rerata_arus_dc(uint8_t berapa_kali,uint8_t pin_adc){
	float arus;
	for(uint8_t i=0;i<berapa_kali;i++){
		arus+=(skala_acs*((float)analogRead(pin_adc)-(float)titik_nol)*tegangan_referensi/resolusi_adc);
	}
	return arus/berapa_kali;
}
//set titik nol adc pada sensor acs712	
void idwr_acs712::set_titik_nol(int nol){
	titik_nol=nol;
}

//set tegangan referensi yang digunakan	
void idwr_acs712::set_vref(float vref){
	tegangan_referensi=vref;
}

//set skala baru jika pembacaab ACS melalui penguat	
void idwr_acs712::set_skala(float skala_baru){
	skala_acs=skala_baru;
}

//mencari titik nol adc dari acs712
int idwr_acs712::kalibrasi(uint8_t pin_adc){
	int nol = 0;
	for (uint8_t i = 0; i < 10; i++) {
		nol += analogRead(pin_adc);
		delay(10);
	}
	nol /= 10;
	titik_nol = nol;
	return nol;
}
	