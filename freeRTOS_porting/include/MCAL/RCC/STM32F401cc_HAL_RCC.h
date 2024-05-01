/*
 * STM32F401cc_HAL_RCC.h
 *
 *  Created on: Feb 5, 2024
 *      Author: Aly Mahmoud
 */


#ifndef MCAL_RCC_STM32F401CC_HAL_RCC_H_
	#define MCAL_RCC_STM32F401CC_HAL_RCC_H_

	/*Includes*/
		#include "Std_Types.h"
		#include "Bit_Mask.h"
	/*-------*/

	/*#defines*/

		/*
		 Here you notice that SYSCLK_<Something> so, 
			the DevUser Can Write SYSCLK_ and Press tab to AUTO COMPLETE easily
		*/

		/*---Mask for CLK_CTRL--*/
			#define CLK_HSI		 				BIT00_MASK
			#define CLK_HSE  	 				BIT16_MASK
			#define CLK_PLL 	   				BIT24_MASK
			#define CLK_PLLI2S					BIT26_MASK
		/*----------------------*/

		/* Mask for READ_CLK_STATUS*/
			#define READ_HSI_STATUS		     	BIT01_MASK
			#define READ_HSE_STATUS       	    BIT17_MASK
			#define READ_PLL_STATUS 			BIT25_MASK
			#define READ_PLLI2S_STATUS      	BIT27_MASK
		/*------------------*/

		/*Mask for PLL_SRC*/	
			#define PLLSRC_HSI 	       			BITNULL_MASK
			#define PLLSRC_HSE		 			BIT22_MASK
		/*----------------*/

		/*Mask for SYSCLK_CLK*/
			#define SYSCLK_HSI					BITNULL_MASK
			#define SYSCLK_HSE					BIT01_MASK
			#define SYSCLK_PLL					BIT02_MASK		
		/*-------------------*/

		/*Mask for READ_SYSCLK_SRC*/
			#define SYSCLK_STATUS                0x0000000C
		/*------------------------*/

		/*Mask for AHB_PREscalar*/
			#define AHB_PRE_1					0x00000000
			#define AHB_PRE_2					0x00000080
			#define AHB_PRE_4 					0x00000090
			#define AHB_PRE_8 					0x000000A0
			#define AHB_PRE_16 					0x000000B0
			#define AHB_PRE_64 					0x000000C0
			#define AHB_PRE_128 				0x000000D0
			#define AHB_PRE_256 				0x000000E0
			#define AHB_PRE_512					0x000000F0
		/*----------------------*/	

		/*Mask for AHB1ENR_PERI*/
			#define AHB1ENR_PERI_VERFI_BIT      BIT31_MASK

			#define AHB1ENR_DMA2                ( AHB1ENR_PERI_VERFI_BIT | BIT22_MASK )
			#define AHB1ENR_DMA1				( AHB1ENR_PERI_VERFI_BIT | BIT21_MASK )
			#define AHB1ENR_CRC					( AHB1ENR_PERI_VERFI_BIT | BIT12_MASK )
			#define AHB1ENR_GPOIH               ( AHB1ENR_PERI_VERFI_BIT | BIT07_MASK )
			#define AHB1ENR_GPOIE               ( AHB1ENR_PERI_VERFI_BIT | BIT04_MASK )
			#define AHB1ENR_GPOID				( AHB1ENR_PERI_VERFI_BIT | BIT03_MASK )
			#define AHB1ENR_GPOIC               ( AHB1ENR_PERI_VERFI_BIT | BIT02_MASK )
			#define AHB1ENR_GPOIB               ( AHB1ENR_PERI_VERFI_BIT | BIT01_MASK )
			#define AHB1ENR_GPOIA               ( AHB1ENR_PERI_VERFI_BIT | BIT00_MASK )
		/*-----------------*/

		/*Mask for AHB2ENR_PERI*/
			#define AHB2ENR_PERI_VERFI_BIT        BIT30_MASK

			#define AHB2ENR_OTGFS               ( BIT30_MASK | BIT07_MASK )
		/*----------------*/

		/* Masks for PPRE1: APB Low-speed prescaler (APB1) */
			#define APB_PRE1_1   			 0x00000000
			#define APB_PRE1_2   			 0x00000400 
			#define APB_PRE1_4   			 0x00000500 
			#define APB_PRE1_8   			 0x00000600 
			#define APB_PRE1_16  			 0x00000700 
		/*-------------------------------------------------*/		

		/*Mask for APB1ENR_PERI*/
			#define APB1ENR_PERI_VERFI_BIT        BIT29_MASK			

			#define APB1ENR_PWR					( APB1ENR_PERI_VERFI_BIT | BIT28_MASK )
			#define APB1ENR_I2C3				( APB1ENR_PERI_VERFI_BIT | BIT23_MASK )
			#define APB1ENR_I2C2				( APB1ENR_PERI_VERFI_BIT | BIT22_MASK )
			#define APB1ENR_I2C1				( APB1ENR_PERI_VERFI_BIT | BIT21_MASK )
			#define APB1ENR_USART				( APB1ENR_PERI_VERFI_BIT | BIT17_MASK )
			#define APB1ENR_SPI3				( APB1ENR_PERI_VERFI_BIT | BIT15_MASK )
			#define APB1ENR_SPI2				( APB1ENR_PERI_VERFI_BIT | BIT14_MASK ) 
			#define APB1ENR_WWDG				( APB1ENR_PERI_VERFI_BIT | BIT11_MASK )
			#define APB1ENR_TIM5				( APB1ENR_PERI_VERFI_BIT | BIT03_MASK )
			#define APB1ENR_TIM4				( APB1ENR_PERI_VERFI_BIT | BIT02_MASK )
			#define APB1ENR_TIM3				( APB1ENR_PERI_VERFI_BIT | BIT01_MASK )
			#define APB1ENR_TIM2 				( APB1ENR_PERI_VERFI_BIT | BIT00_MASK )
		/*---------------*/	

		/* Masks for PPRE2: APB high-speed prescaler (APB2) */
			#define APB_PRE2_1   				 0x00000000 
			#define APB_PRE2_2   				 0x00002000 
			#define APB_PRE2_4   				 0x00002800 
			#define APB_PRE2_8   				 0x00003000 
			#define APB_PRE2_16  				 0x00003800 
		/*-------------------------------------------------*/		

		/*Mask for APB2ENR_PERI*/
			#define APB2ENR_PERI_VERFI_BIT        BIT20_MASK

			#define APB2ENR_TIM11               ( APB2ENR_PERI_VERFI_BIT | BIT18_MASK )
			#define APB2ENR_TIM10               ( APB2ENR_PERI_VERFI_BIT | BIT17_MASK )
			#define APB2ENR_TIM09               ( APB2ENR_PERI_VERFI_BIT | BIT16_MASK )
			#define APB2ENR_SYSCFG              ( APB2ENR_PERI_VERFI_BIT | BIT14_MASK )
			#define APB2ENR_SPI4                ( APB2ENR_PERI_VERFI_BIT | BIT13_MASK )
			#define APB2ENR_SPI1                ( APB2ENR_PERI_VERFI_BIT | BIT12_MASK ) 
			#define APB2ENR_SDIO                ( APB2ENR_PERI_VERFI_BIT | BIT11_MASK ) 
			#define APB2ENR_ADC1                ( APB2ENR_PERI_VERFI_BIT | BIT08_MASK ) 
			#define APB2ENR_USART6              ( APB2ENR_PERI_VERFI_BIT | BIT05_MASK )
			#define APB2ENR_USART1              ( APB2ENR_PERI_VERFI_BIT | BIT04_MASK )
			#define APB2ENR_TIM1                ( APB2ENR_PERI_VERFI_BIT | BIT00_MASK )

		/*---------------*/

	/*--------*/

	/*New types*/

		/*Enums*/

			/*Error Enum*/
				typedef enum 
				{
					RCC_OK,
					RCC_NOK,
					RCC_InputError,
					RCC_ClockNotON,
					RCC_ClockNotReady,
					RCC_PLLON,
				}RCC_enuErrorStatus_t;
			/*----------*/

			/*Status Enum*/
				typedef enum
				{
						NotReady,
						Ready,
						Wrong_Input
				}RCC_CLKStatus_t;
			/*-----------*/

			/*SYSCLK STATUS enum*/
				typedef enum
				{
					HSI,
					HSE,
					PLL
				}RCC_SYSCLKStatus_t;
			/*------------------*/

		/*-----*/

	/*---------*/

	/*API's*/

		/*Naming Conventions of API*/
					//    ErrorStatus_Driver_<Operation><On_What> ( Data type On_What )
			//Example ->
					//    ErrorStatus_RCC_SelectSYSCLK (uint8_t SYSCLK)
		/*-------------------------*/

		/*CLK Control functions*/	

			/*-----Function for Enable any CLK----*/
				RCC_enuErrorStatus_t RCC_EnableClock				( U32 CLK_CLK );
			/*------------------------------------*/

			/*-----Function for Disaple any CLK----*/
				RCC_enuErrorStatus_t RCC_DisableClock				( U32 CLK_CLK );
			/*-------------------------------------*/

			/*Function for Configuration of PLL SRC */
				RCC_enuErrorStatus_t RCC_PLL_SRCConfig				( U32 PLLSRC_CLK );
			/*--------------------------------------------*/

			/*Function for Configuration of PLL Pre Scalar*/
				RCC_enuErrorStatus_t	RCC_PLL_PreScalarConfig	( U8 Copy_u8PLLM , U32 Copy_u16PLLN , U8 Copy_u8PLLQ , U8 Copy_u8PLLP );
			/*--------------------------------------------*/		

			/*----Function for Reading any CLK status----*/
				RCC_CLKStatus_t	RCC_ReadStatusClock					( U32 READ_CLK_STATUS );
			/*-------------------------------------------*/

			/*Function to Choose the desired system clk source*/
				RCC_enuErrorStatus_t RCC_SetSYSCLK 				 	(    U32 SYSCLK_CLK    );
			/*------------------------------------------------*/

			/*Function to Reading SYSCLK source*/
				RCC_SYSCLKStatus_t RCC_ReadSYSCLKStatus 		    (  					  );
			/*---------------------------------*/

		/*---------------------*/

		/*Peripheral Control*/
			
			/*AHB1*/

				/*AHB1_PREscalar*/
					RCC_enuErrorStatus_t RCC_AHB_PREscaler			(  	  U32 AHB_PREscalar    );
				/*--------------*/

				/*AHB1 Set*/
					RCC_enuErrorStatus_t RCC_SetAHB1Peripheral		(		U32 AHB1ENR_PERI	);
				/*--------*/

				/*AHB1 Reset*/
					RCC_enuErrorStatus_t RCC_ResetAHB1Peripheral	(		U32 AHB1ENR_PERI	);
				/*----------*/

			/*----*/

			/*AHB2*/

				/*AHB2 Set*/
					RCC_enuErrorStatus_t RCC_SetAHB2Peripheral		(		U32 AHB2ENR_PERI		);
				/*--------*/

				/*AHB2 Reset*/
					RCC_enuErrorStatus_t RCC_ResetAHB2Peripheral	(		U32 AHB2ENR_PERI		);
				/*---------*/

			/*----*/

			/*APB1*/

				/*APB1_PREscalar*/
					RCC_enuErrorStatus_t RCC_APB1_PREscaler			(    U32 APB1_PREscalar    );
				/*--------------*/			

				/*APB1 Set*/
					RCC_enuErrorStatus_t RCC_SetAPB1Peripheral		(		U32 APB1ENR_PERI	);
				/*--------*/

				/*APB1 Reset*/
					RCC_enuErrorStatus_t RCC_ResetAPB1Peripheral	(		U32 APB1ENR_PERI	);
				/*----------*/

			/*----*/

			/*APB2*/

				/*APB2_PREscalar*/
					RCC_enuErrorStatus_t RCC_APB2_PREscaler			(    U32 APB2_PREscalar    );
				/*--------------*/	

				/*APB2 Set*/
					RCC_enuErrorStatus_t RCC_SetAPB2Peripheral		(		U32 AP2ENR_PERI		);
				/*--------*/

				/*APB2 Reset*/
					RCC_enuErrorStatus_t RCC_SetAPB2Peripheral		(		U32 AP2ENR_PERI		);
				/*---------*/

			/*----*/
			
		/*------------------*/

	/*-----*/
	
#endif /* MCAL_RCC_STM32F401CC_HAL_RCC_H_ */

