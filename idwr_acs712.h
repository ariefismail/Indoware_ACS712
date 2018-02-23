#ifndef idwr_acs712_h
#define idwr_acs712_h

#include <Arduino.h>

#define resolusi_adc 1023

class idwr_acs712 {
public:
	idwr_acs712(uint8_t type_sensor_acs712, float vref);
	
	//ambil nilai adc pada pin dan konversikan langung dalam bentuk arus AMPERE
	float arus_dc(uint8_t pin_adc);
	
	float rerata_arus_dc(uint8_t berapa_kali,uint8_t pin_adc);

	//set titik nol adc pada sensor acs712	
	void set_titik_nol(int nol);

	//set tegangan referensi yang digunakan	
	void set_vref(float vref);

	//set skala baru jika pembacaab ACS melalui penguat	
	void set_skala(float skala_baru);

	//mencari titik nol adc dari acs712
	int kalibrasi(uint8_t pin_adc);

private:
	int titik_nol = 512;
	uint8_t pin_pembacaan_adc;
	float skala_acs;
	float tegangan_referensi=5;
};

#endif