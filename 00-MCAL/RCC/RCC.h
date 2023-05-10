/*************************************************************
 * 
 * Filename: RCC.h
 * Description: Header (interface) file of the RCC driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __RCC_H__
#define __RCC_H__

#include "STD_TYPES.h"
#include "RCC_Cfg.h"
#include "RCC_Priv.h"


#define CONC(a,b)  a##b
#define CONCAT(a,b) CONC(a,b)

#define SysClk_HSI_SW 0b00
#define SysClk_HSE_SW 0b01
#define SysClk_PLL_SW 0b10

#define PLLSRC_HSI 0
#define PLLSRC_HSE 1

#define PLLQ_02  02
#define PLLQ_03  03
#define PLLQ_04  04
#define PLLQ_05  05
#define PLLQ_06  06
#define PLLQ_07  07
#define PLLQ_08  08
#define PLLQ_09  09
#define PLLQ_10  10
#define PLLQ_11  11
#define PLLQ_12  12
#define PLLQ_13  13
#define PLLQ_14  14
#define PLLQ_15  15

#define PLLP_02 0b00
#define PLLP_04 0b01
#define PLLP_06 0b10
#define PLLP_08 0b11

#define PLLN_192 192
#define PLLN_193 193
#define PLLN_194 194
#define PLLN_195 195
#define PLLN_196 196
#define PLLN_197 197
#define PLLN_198 198
#define PLLN_199 199
#define PLLN_200 200
#define PLLN_201 201
#define PLLN_202 202
#define PLLN_203 203
#define PLLN_204 204
#define PLLN_205 205
#define PLLN_206 206
#define PLLN_207 207
#define PLLN_208 208
#define PLLN_209 209
#define PLLN_210 210
#define PLLN_211 211
#define PLLN_212 212
#define PLLN_213 213
#define PLLN_214 214
#define PLLN_215 215
#define PLLN_216 216
#define PLLN_217 217
#define PLLN_218 218
#define PLLN_219 219
#define PLLN_220 220
#define PLLN_221 221
#define PLLN_222 222
#define PLLN_223 223
#define PLLN_224 224
#define PLLN_225 225
#define PLLN_226 226
#define PLLN_227 227
#define PLLN_228 228
#define PLLN_229 229
#define PLLN_230 230
#define PLLN_231 231
#define PLLN_232 232
#define PLLN_233 233
#define PLLN_234 234
#define PLLN_235 235
#define PLLN_236 236
#define PLLN_237 237
#define PLLN_238 238
#define PLLN_239 239
#define PLLN_240 240
#define PLLN_241 241
#define PLLN_242 242
#define PLLN_243 243
#define PLLN_244 244
#define PLLN_245 245
#define PLLN_246 246
#define PLLN_247 247
#define PLLN_248 248
#define PLLN_249 249
#define PLLN_250 250
#define PLLN_251 251
#define PLLN_252 252
#define PLLN_253 253
#define PLLN_254 254
#define PLLN_255 255
#define PLLN_256 256
#define PLLN_257 257
#define PLLN_258 258
#define PLLN_259 259
#define PLLN_260 260
#define PLLN_261 261
#define PLLN_262 262
#define PLLN_263 263
#define PLLN_264 264
#define PLLN_265 265
#define PLLN_266 266
#define PLLN_267 267
#define PLLN_268 268
#define PLLN_269 269
#define PLLN_270 270
#define PLLN_271 271
#define PLLN_272 272
#define PLLN_273 273
#define PLLN_274 274
#define PLLN_275 275
#define PLLN_276 276
#define PLLN_277 277
#define PLLN_278 278
#define PLLN_279 279
#define PLLN_280 280
#define PLLN_281 281
#define PLLN_282 282
#define PLLN_283 283
#define PLLN_284 284
#define PLLN_285 285
#define PLLN_286 286
#define PLLN_287 287
#define PLLN_288 288
#define PLLN_289 289
#define PLLN_290 290
#define PLLN_291 291
#define PLLN_292 292
#define PLLN_293 293
#define PLLN_294 294
#define PLLN_295 295
#define PLLN_296 296
#define PLLN_297 297
#define PLLN_298 298
#define PLLN_299 299
#define PLLN_300 300
#define PLLN_301 301
#define PLLN_302 302
#define PLLN_303 303
#define PLLN_304 304
#define PLLN_305 305
#define PLLN_306 306
#define PLLN_307 307
#define PLLN_308 308
#define PLLN_309 309
#define PLLN_310 310
#define PLLN_311 311
#define PLLN_312 312
#define PLLN_313 313
#define PLLN_314 314
#define PLLN_315 315
#define PLLN_316 316
#define PLLN_317 317
#define PLLN_318 318
#define PLLN_319 319
#define PLLN_320 320
#define PLLN_321 321
#define PLLN_322 322
#define PLLN_323 323
#define PLLN_324 324
#define PLLN_325 325
#define PLLN_326 326
#define PLLN_327 327
#define PLLN_328 328
#define PLLN_329 329
#define PLLN_330 330
#define PLLN_331 331
#define PLLN_332 332
#define PLLN_333 333
#define PLLN_334 334
#define PLLN_335 335
#define PLLN_336 336
#define PLLN_337 337
#define PLLN_338 338
#define PLLN_339 339
#define PLLN_340 340
#define PLLN_341 341
#define PLLN_342 342
#define PLLN_343 343
#define PLLN_344 344
#define PLLN_345 345
#define PLLN_346 346
#define PLLN_347 347
#define PLLN_348 348
#define PLLN_349 349
#define PLLN_350 350
#define PLLN_351 351
#define PLLN_352 352
#define PLLN_353 353
#define PLLN_354 354
#define PLLN_355 355
#define PLLN_356 356
#define PLLN_357 357
#define PLLN_358 358
#define PLLN_359 359
#define PLLN_360 360
#define PLLN_361 361
#define PLLN_362 362
#define PLLN_363 363
#define PLLN_364 364
#define PLLN_365 365
#define PLLN_366 366
#define PLLN_367 367
#define PLLN_368 368
#define PLLN_369 369
#define PLLN_370 370
#define PLLN_371 371
#define PLLN_372 372
#define PLLN_373 373
#define PLLN_374 374
#define PLLN_375 375
#define PLLN_376 376
#define PLLN_377 377
#define PLLN_378 378
#define PLLN_379 379
#define PLLN_380 380
#define PLLN_381 381
#define PLLN_382 382
#define PLLN_383 383
#define PLLN_384 384
#define PLLN_385 385
#define PLLN_386 386
#define PLLN_387 387
#define PLLN_388 388
#define PLLN_389 389
#define PLLN_390 390
#define PLLN_391 391
#define PLLN_392 392
#define PLLN_393 393
#define PLLN_394 394
#define PLLN_395 395
#define PLLN_396 396
#define PLLN_397 397
#define PLLN_398 398
#define PLLN_399 399
#define PLLN_400 400
#define PLLN_401 401
#define PLLN_402 402
#define PLLN_403 403
#define PLLN_404 404
#define PLLN_405 405
#define PLLN_406 406
#define PLLN_407 407
#define PLLN_408 408
#define PLLN_409 409
#define PLLN_410 410
#define PLLN_411 411
#define PLLN_412 412
#define PLLN_413 413
#define PLLN_414 414
#define PLLN_415 415
#define PLLN_416 416
#define PLLN_417 417
#define PLLN_418 418
#define PLLN_419 419
#define PLLN_420 420
#define PLLN_421 421
#define PLLN_422 422
#define PLLN_423 423
#define PLLN_424 424
#define PLLN_425 425
#define PLLN_426 426
#define PLLN_427 427
#define PLLN_428 428
#define PLLN_429 429
#define PLLN_430 430
#define PLLN_431 431
#define PLLN_432 432

#define PLLM_02  02
#define PLLM_03  03
#define PLLM_04  04
#define PLLM_05  05
#define PLLM_06  06
#define PLLM_07  07
#define PLLM_08  08
#define PLLM_09  09
#define PLLM_10  10
#define PLLM_11  11
#define PLLM_12  12
#define PLLM_13  13
#define PLLM_14  14
#define PLLM_15  15
#define PLLM_16  16
#define PLLM_17  17
#define PLLM_18  18
#define PLLM_19  19
#define PLLM_20  20
#define PLLM_21  21
#define PLLM_22  22
#define PLLM_23  23
#define PLLM_24  24
#define PLLM_25  25
#define PLLM_26  26
#define PLLM_27  27
#define PLLM_28  28
#define PLLM_29  29
#define PLLM_30  30
#define PLLM_31  31
#define PLLM_32  32
#define PLLM_33  33
#define PLLM_34  34
#define PLLM_35  35
#define PLLM_36  36
#define PLLM_37  37
#define PLLM_38  38
#define PLLM_39  39
#define PLLM_40  40
#define PLLM_41  41
#define PLLM_42  42
#define PLLM_43  43
#define PLLM_44  44
#define PLLM_45  45
#define PLLM_46  46
#define PLLM_47  47
#define PLLM_48  48
#define PLLM_49  49
#define PLLM_50  50
#define PLLM_51  51
#define PLLM_52  52
#define PLLM_53  53
#define PLLM_54  54
#define PLLM_55  55
#define PLLM_56  56
#define PLLM_57  57
#define PLLM_58  58
#define PLLM_59  59
#define PLLM_60  60
#define PLLM_61  61
#define PLLM_62  62
#define PLLM_63  63

#define PLLM_MASK 0xffffffc0
#define PLLN_MASK 0xffff803f
#define PLLP_MASK 0xfffcffff
#define PLLQ_MASK 0xf03fffff
#define SW_MASK   0xfffffffc
#define MCO2_MASK 0x3fffffff
#define MCO1_MASK 0xff9fffff
#define MCO2PRE_MASK 0xc7ffffff
#define MCO1PRE_MASK 0xf8ffffff
#define I2SSRC_MASK  0xff7fffff
#define RTCPRE_MASK  0xffe0ffff
#define APB1_PPRE1_MASK 0xffffe3ff
#define APB2_PPRE2_MASK 0xffff1fff
#define AHB_HPRE_MASK 0Xffffff0f
/**********RCC_CFGR***********/
#define MCO2_SelClk_SYSCLK 0b00
#define MCO2_SelClk_PLLI2S 0b01
#define MCO2_SelClk_HSE    0b10
#define MCO2_SelClk_PLL    0b11

#define MCO1_SelClk_HSI  0b00
#define MCO1_SelClk_LSE	 0b01
#define MCO1_SelClk_HSE  0b10
#define MCO1_SelClk_PLL  0b11

#define MCO1DivBy_NODIV 0b000
#define MCO1DivBy_2 	0b100
#define MCO1DivBy_3 	0b101
#define MCO1DivBy_4		0b110
#define MCO1DivBy_5 	0b111

#define MCO2DivBy_NODIV 0b000
#define MCO2DivBy_2 	0b100
#define MCO2DivBy_3 	0b101
#define MCO2DivBy_4		0b110
#define MCO2DivBy_5 	0b111

#define I2SSRC_PLLI2S	0
#define I2SSRC_I2S_CKIN 1

#define RTC_HSEDivBy_NO0 0B00000
#define RTC_HSEDivBy_NO1 0B00001
#define RTC_HSEDivBy_02 0B00010
#define RTC_HSEDivBy_03 0B00011
#define RTC_HSEDivBy_04 0B00100
#define RTC_HSEDivBy_05  0B00101
#define RTC_HSEDivBy_06  0B00110
#define RTC_HSEDivBy_07  0B00111
#define RTC_HSEDivBy_08  0B01000
#define RTC_HSEDivBy_09  0B01001
#define RTC_HSEDivBy_10  0B01010
#define RTC_HSEDivBy_11  0B01011
#define RTC_HSEDivBy_12  0B01100
#define RTC_HSEDivBy_13  0B01101
#define RTC_HSEDivBy_14  0B01110
#define RTC_HSEDivBy_15  0B01111
#define RTC_HSEDivBy_16  0B10000
#define RTC_HSEDivBy_17  0B10001
#define RTC_HSEDivBy_18  0B10010
#define RTC_HSEDivBy_19  0B10011
#define RTC_HSEDivBy_20  0B10100
#define RTC_HSEDivBy_21  0B10101
#define RTC_HSEDivBy_22  0B10110
#define RTC_HSEDivBy_23  0B10111
#define RTC_HSEDivBy_24  0B11000
#define RTC_HSEDivBy_25  0B11001
#define RTC_HSEDivBy_26  0B11010
#define RTC_HSEDivBy_27  0B11011
#define RTC_HSEDivBy_28  0B11100
#define RTC_HSEDivBy_29  0B11101
#define RTC_HSEDivBy_30  0B11110
#define RTC_HSEDivBy_31  0B11111

#define AHBClkDiv_NO  0B000
#define AHBClkDiv_02  0B100
#define AHBClkDiv_04  0B101
#define AHBClkDiv_08  0B110
#define AHBClkDiv_16  0B111

#define SysClkDivBy_NO   0000
#define SysClkDivBy_002  0b1000
#define SysClkDivBy_004  0b1001
#define SysClkDivBy_008  0b1010
#define SysClkDivBy_016  0b1011
#define SysClkDivBy_064  0b1100
#define SysClkDivBy_128  0b1101
#define SysClkDivBy_256  0b1110
#define SysClkDivBy_512  0b1111
/*AHB1RSTR & AHB2RSTR register*/

#define AXBRSTR_RESET 1
/* AHB1ENR*/
#define AXBENR_Clk_ENABLED 1
#define AXBENR_Clk_DISABLED 0


typedef enum
{
	rcc_enuOK,
	rcc_enuNOK,
	rcc_enuNullPtr,
	rcc_enuInvalidParameter,
	rcc_enuPLLIsAlreadyConfigured,
} rcc_enuErrorStatus_t;

typedef enum{
	RCC_CR_enuHSION=0,
	RCC_CR_enuHSIRDY,
	RCC_CR_enuReserved2,
	RCC_CR_enuHSITRIM_0,
	RCC_CR_enuHSITRIM_1,
	RCC_CR_enuHSITRIM_2,
	RCC_CR_enuHSITRIM_3,
	RCC_CR_enuHSITRIM_4,
	RCC_CR_enuHSICAL_0 ,
	RCC_CR_enuHSICAL_1 ,
	RCC_CR_enuHSICAL_2 ,
	RCC_CR_enuHSICAL_3 ,
	RCC_CR_enuHSICAL_4 ,
	RCC_CR_enuHSICAL_5 ,
	RCC_CR_enuHSICAL_6 ,
	RCC_CR_enuHSICAL_7 ,
	RCC_CR_enuHSEON ,
	RCC_CR_enuHSERDY ,
	RCC_CR_enuHSEBYP ,
	RCC_CR_enuCSSON ,
	RCC_CR_enuReserved20,
	RCC_CR_enuReserved21,
	RCC_CR_enuReserved22,
	RCC_CR_enuReserved23,
	RCC_CR_enuPLLON 	,
	RCC_CR_enuPLLRDY 	,
	RCC_CR_enuPLLI2SON 	,
	RCC_CR_enuPLLI2SRDY ,
	RCC_CR_enuReserved28,
	RCC_CR_enuReserved29,
	RCC_CR_enuReserved30,
	RCC_CR_enuReserved31,
	RCC_CR_enuBitsNumber
}tenu_RCC_CR_Bits;



typedef enum{
	RCC_PLLCFGR_enuPLLM0=0,
	RCC_PLLCFGR_enuPLLM1,
	RCC_PLLCFGR_enuPLLM2,
	RCC_PLLCFGR_enuPLLM3,
	RCC_PLLCFGR_enuPLLM4,
	RCC_PLLCFGR_enuPLLM5,
	RCC_PLLCFGR_enuPLLN0,
	RCC_PLLCFGR_enuPLLN1,
	RCC_PLLCFGR_enuPLLN2,
	RCC_PLLCFGR_enuPLLN3,
	RCC_PLLCFGR_enuPLLN4,
	RCC_PLLCFGR_enuPLLN5,
	RCC_PLLCFGR_enuPLLN6,
	RCC_PLLCFGR_enuPLLN7,
	RCC_PLLCFGR_enuPLLN8,
	RCC_PLLCFGR_enuReserved15,
	RCC_PLLCFGR_enuPLLP0,
	RCC_PLLCFGR_enuPLLP1,
	RCC_PLLCFGR_enuReserved18,
	RCC_PLLCFGR_enuReserved19,
	RCC_PLLCFGR_enuReserved20,
	RCC_PLLCFGR_enuReserved21,
	RCC_PLLCFGR_enuPLLSRC	 ,
	RCC_PLLCFGR_enuReserved23,
	RCC_PLLCFGR_enuPLLQ0     ,
	RCC_PLLCFGR_enuPLLQ1     ,
	RCC_PLLCFGR_enuPLLQ2     ,
	RCC_PLLCFGR_enuPLLQ3     ,
	RCC_PLLCFGR_enuReserved28,
	RCC_PLLCFGR_enuReserved29,
	RCC_PLLCFGR_enuReserved30,
	RCC_PLLCFGR_enuReserved31,
	RCC_PLLCFGR_enuBitsNumber

 }tenuRCC_PLLCFGR_Bits;

typedef enum	{
	RCC_CFGR_enuSW0 =0,
	RCC_CFGR_enuSW1,
	RCC_CFGR_enuSWS0,
	RCC_CFGR_enuSWS1,
	RCC_CFGR_enuHPRE0,
	RCC_CFGR_enuHPRE1,
	RCC_CFGR_enuHPRE2,
	RCC_CFGR_enuHPRE3,
	RCC_CFGR_enuReserved8,
	RCC_CFGR_enuReserved9,
	RCC_CFGR_enuPPRE10	 ,
	RCC_CFGR_enuPPRE11	 ,
	RCC_CFGR_enuPPRE12	 ,
	RCC_CFGR_enuPPRE20	 ,
	RCC_CFGR_enuPPRE21	 ,
	RCC_CFGR_enuPPRE22	 ,
	RCC_CFGR_enuRTCPRE0	 ,
	RCC_CFGR_enuRTCPRE1	 ,
	RCC_CFGR_enuRTCPRE2	 ,
	RCC_CFGR_enuRTCPRE3	 ,
	RCC_CFGR_enuRTCPRE4	 ,
	RCC_CFGR_enuMCO10	 ,
	RCC_CFGR_enuMCO11	 ,
	RCC_CFGR_enuI2SSRC	 ,
	RCC_CFGR_enuMCO1PRE0 ,
	RCC_CFGR_enuMCO1PRE1 ,
	RCC_CFGR_enuMCO1PRE2 ,
	RCC_CFGR_enuMCO2PRE0 ,
	RCC_CFGR_enuMCO2PRE1 ,
	RCC_CFGR_enuMCO2PRE2 ,
	RCC_CFGR_enuMCO20	 ,
	RCC_CFGR_enuMCO21	 ,
	RCC_CFGR_enuBitsNumber
 }tenuRCC_CFGR_Bits;

 typedef enum
 {
  	RCC_AHB1RSTR_enuGPIOARST,
  	RCC_AHB1RSTR_enuGPIOBRST,
  	RCC_AHB1RSTR_enuGPIOCRST,
  	RCC_AHB1RSTR_enuGPIODRST,
  	RCC_AHB1RSTR_enuGPIOERST,
  	RCC_AHB1RSTR_enuReserved0,
  	RCC_AHB1RSTR_enuReserved1,
    RCC_AHB1RSTR_enuGPIOHRST,
  	RCC_AHB1RSTR_enuReserved2,
  	RCC_AHB1RSTR_enuReserved3,
  	RCC_AHB1RSTR_enuReserved4,
  	RCC_AHB1RSTR_enuReserved5,
  	RCC_AHB1RSTR_enuCRCRST,
  	RCC_AHB1RSTR_enuReserved06,
  	RCC_AHB1RSTR_enuReserved07,
  	RCC_AHB1RSTR_enuReserved08,
  	RCC_AHB1RSTR_enuReserved09,
  	RCC_AHB1RSTR_enuReserved10,
  	RCC_AHB1RSTR_enuReserved11,
  	RCC_AHB1RSTR_enuReserved12,
  	RCC_AHB1RSTR_enuReserved13,
  	RCC_AHB1RSTR_enuDMA1RST,
  	RCC_AHB1RSTR_enuDMA2RST,
  	RCC_AHB1RSTR_enuReserved14,
  	RCC_AHB1RSTR_enuReserved15,
  	RCC_AHB1RSTR_enuReserved16,
  	RCC_AHB1RSTR_enuReserved17,
  	RCC_AHB1RSTR_enuReserved18,
  	RCC_AHB1RSTR_enuReserved19,
  	RCC_AHB1RSTR_enuReserved20,
  	RCC_AHB1RSTR_enuReserved21,
  	RCC_AHB1RSTR_enuReserved22,
  	RCC_AHB1RSTR_enuBitsNumber,
   }tenuRCC_AHB1RSTR_Bits;

   typedef enum
   {
	RCC_AHB2RSTR_enuReserved0,
	RCC_AHB2RSTR_enuReserved1,
	RCC_AHB2RSTR_enuReserved2,
	RCC_AHB2RSTR_enuReserved3,
	RCC_AHB2RSTR_enuReserved4,
	RCC_AHB2RSTR_enuReserved5,
	RCC_AHB2RSTR_enuReserved06,
	RCC_AHB2RSTR_enuOTGFSRST,
	RCC_AHB2RSTR_enuReserved07,
	RCC_AHB2RSTR_enuReserved08,
	RCC_AHB2RSTR_enuReserved09,
	RCC_AHB2RSTR_enuReserved10,
	RCC_AHB2RSTR_enuReserved11,
	RCC_AHB2RSTR_enuReserved12,
	RCC_AHB2RSTR_enuReserved13,
	RCC_AHB2RSTR_enuReserved14,
	RCC_AHB2RSTR_enuReserved15,
	RCC_AHB2RSTR_enuReserved16,
	RCC_AHB2RSTR_enuReserved17,
	RCC_AHB2RSTR_enuReserved18,
	RCC_AHB2RSTR_enuReserved19,
	RCC_AHB2RSTR_enuReserved20,
	RCC_AHB2RSTR_enuReserved21,
	RCC_AHB2RSTR_enuReserved22,
	RCC_AHB2RSTR_enuReserved23,
	RCC_AHB2RSTR_enuReserved24,
	RCC_AHB2RSTR_enuReserved25,
	RCC_AHB2RSTR_enuReserved26,
	RCC_AHB2RSTR_enuReserved27,
	RCC_AHB2RSTR_enuReserved28,
	RCC_AHB2RSTR_enuReserved29,
	RCC_AHB2RSTR_enuReserved30,
	RCC_AHB2RSTR_enuBitsNumber,
}tenuRCC_AHB2RSTR_Bits;

typedef enum{
	RCC_APB1RSTR_enuTIM2RST,
	RCC_APB1RSTR_enuTIM3RST,
	RCC_APB1RSTR_enuTIM4RST,
	RCC_APB1RSTR_enuTIM5RST,
	RCC_APB1RSTR_enuReserved00,
	RCC_APB1RSTR_enuReserved01,
	RCC_APB1RSTR_enuReserved02,
	RCC_APB1RSTR_enuReserved03,
	RCC_APB1RSTR_enuReserved04,
	RCC_APB1RSTR_enuReserved05,
	RCC_APB1RSTR_enuReserved06,
	RCC_APB1RSTR_enuWWDGRST,
	RCC_APB1RSTR_enuReserved07,
	RCC_APB1RSTR_enuReserved08,
	RCC_APB1RSTR_enuSPI2RST,
	RCC_APB1RSTR_enuSPI3RST,
	RCC_APB1RSTR_enuReserved09,
	RCC_APB1RSTR_enuUSART2RST,
	RCC_APB1RSTR_enuReserved10,
	RCC_APB1RSTR_enuReserved11,
	RCC_APB1RSTR_enuReserved12,
	RCC_APB1RSTR_enuI2C1RST,
	RCC_APB1RSTR_enuI2C2RST,
	RCC_APB1RSTR_enuI2C3RST,
	RCC_APB1RSTR_enuReserved13,
	RCC_APB1RSTR_enuReserved14,
	RCC_APB1RSTR_enuReserved15,
	RCC_APB1RSTR_enuReserved16,
	RCC_APB1RSTR_enuPWRRST,
	RCC_APB1RSTR_enuReserved17,
	RCC_APB1RSTR_enuReserved18,
	RCC_APB1RSTR_enuReserved19,
	RCC_APB1RSTR_enuBitsNumber,
}tenuRCC_APB1RSTR_Bits;

typedef enum{
	RCC_APB2RSTR_enuTIM1RST,
	RCC_APB2RSTR_enuReserved00,
	RCC_APB2RSTR_enuReserved01,
	RCC_APB2RSTR_enuReserved02,
	RCC_APB2RSTR_enuUSART1RST,
	RCC_APB2RSTR_enuUSART6RST,
	RCC_APB2RSTR_enuReserved03,
	RCC_APB2RSTR_enuReserved04,
	RCC_APB2RSTR_enuADC1RST,
	RCC_APB2RSTR_enuReserved05,
	RCC_APB2RSTR_enuReserved06,
	RCC_APB2RSTR_enuSDIORST,
	RCC_APB2RSTR_enuSPI1RST,
	RCC_APB2RSTR_enuSPI4RST,
	RCC_APB2RSTR_enuSYSCFGRST,
	RCC_APB2RSTR_enuReserved07,
	RCC_APB2RSTR_enuTIM9RST,
	RCC_APB2RSTR_enuTIM10RST,
	RCC_APB2RSTR_enuTIM11RST,
	RCC_APB2RSTR_enuReserved08,
	RCC_APB2RSTR_enuReserved09,
	RCC_APB2RSTR_enuReserved10,
	RCC_APB2RSTR_enuReserved11,
	RCC_APB2RSTR_enuReserved12,
	RCC_APB2RSTR_enuReserved13,
	RCC_APB2RSTR_enuReserved14,
	RCC_APB2RSTR_enuReserved15,
	RCC_APB2RSTR_enuReserved16,
	RCC_APB2RSTR_enuReserved17,
	RCC_APB2RSTR_enuReserved18,
	RCC_APB2RSTR_enuReserved19,
	RCC_APB2RSTR_enuReserved20,
	RCC_APB2RSTR_enuBitsNumber,
}tenuRCC_APB2RSTR_Bits;
 typedef enum
 {
 RCC_AHB1ENR_enuGPIOAEN,
 RCC_AHB1ENR_enuGPIOBEN,
 RCC_AHB1ENR_enuGPIOCEN,
 RCC_AHB1ENR_enuGPIODEN,
 RCC_AHB1ENR_enuGPIOEEN,
 RCC_AHB1ENR_enuReserved00,
 RCC_AHB1ENR_enuReserved01,
 RCC_AHB1ENR_enuGPIOHEN,
 RCC_AHB1ENR_enuReserved02,
 RCC_AHB1ENR_enuReserved03,
 RCC_AHB1ENR_enuReserved04,
 RCC_AHB1ENR_enuReserved05,
 RCC_AHB1ENR_enuCRCEN,
 RCC_AHB1ENR_enuReserved06,
 RCC_AHB1ENR_enuReserved07,
 RCC_AHB1ENR_enuReserved08,
 RCC_AHB1ENR_enuReserved09,
 RCC_AHB1ENR_enuReserved10,
 RCC_AHB1ENR_enuReserved11,
 RCC_AHB1ENR_enuReserved12,
 RCC_AHB1ENR_enuReserved13,
 RCC_AHB1ENR_enuDMA1EN,
 RCC_AHB1ENR_enuDMA2EN,
 RCC_AHB1ENR_enuReserved14,
 RCC_AHB1ENR_enuReserved15,
 RCC_AHB1ENR_enuReserved16,
 RCC_AHB1ENR_enuReserved17,
 RCC_AHB1ENR_enuReserved18,
 RCC_AHB1ENR_enuReserved19,
 RCC_AHB1ENR_enuReserved20,
 RCC_AHB1ENR_enuReserved21,
 RCC_AHB1ENR_enuReserved22,
 RCC_AHB1ENR_enuBitsNumber,
 }tenuRCC_AHB1ENR_Bits;


 typedef enum
 {
	RCC_AHB2ENR_enuReserved0,
	RCC_AHB2ENR_enuReserved1,
	RCC_AHB2ENR_enuReserved2,
	RCC_AHB2ENR_enuReserved3,
	RCC_AHB2ENR_enuReserved4,
	RCC_AHB2ENR_enuReserved5,
	RCC_AHB2ENR_enuReserved06,
	RCC_AHB2ENR_enuOTGFSEN,
	RCC_AHB2ENR_enuReserved07,
	RCC_AHB2ENR_enuReserved08,
	RCC_AHB2ENR_enuReserved09,
	RCC_AHB2ENR_enuReserved10,
	RCC_AHB2ENR_enuReserved11,
	RCC_AHB2ENR_enuReserved12,
	RCC_AHB2ENR_enuReserved13,
	RCC_AHB2ENR_enuReserved14,
	RCC_AHB2ENR_enuReserved15,
	RCC_AHB2ENR_enuReserved16,
	RCC_AHB2ENR_enuReserved17,
	RCC_AHB2ENR_enuReserved18,
	RCC_AHB2ENR_enuReserved19,
	RCC_AHB2ENR_enuReserved20,
	RCC_AHB2ENR_enuReserved21,
	RCC_AHB2ENR_enuReserved22,
    RCC_AHB2ENR_enuReserved23,
	RCC_AHB2ENR_enuReserved24,
	RCC_AHB2ENR_enuReserved25,
    RCC_AHB2ENR_enuReserved26,
    RCC_AHB2ENR_enuReserved27,
    RCC_AHB2ENR_enuReserved28,
    RCC_AHB2ENR_enuReserved29,
    RCC_AHB2ENR_enuReserved30,
	RCC_AHB2ENR_enuBitsNumber,
   }tenuRCC_AHB2ENR_Bits;

typedef enum{
	RCC_APB1ENR_enuTIM2EN,
	RCC_APB1ENR_enuTIM3EN,
	RCC_APB1ENR_enuTIM4EN,
	RCC_APB1ENR_enuTIM5EN,
	RCC_APB1ENR_enuReserved00,
	RCC_APB1ENR_enuReserved01,
	RCC_APB1ENR_enuReserved02,
	RCC_APB1ENR_enuReserved03,
	RCC_APB1ENR_enuReserved04,
	RCC_APB1ENR_enuReserved05,
	RCC_APB1ENR_enuReserved06,
	RCC_APB1ENR_enuWWDGEN,
	RCC_APB1ENR_enuReserved07,
	RCC_APB1ENR_enuReserved08,
	RCC_APB1ENR_enuSPI2EN,
	RCC_APB1ENR_enuSPI3EN,
	RCC_APB1ENR_enuReserved09,
	RCC_APB1ENR_enuUSART2EN,
	RCC_APB1ENR_enuReserved10,
	RCC_APB1ENR_enuReserved11,
	RCC_APB1ENR_enuReserved12,
	RCC_APB1ENR_enuI2C1EN,
	RCC_APB1ENR_enuI2C2EN,
	RCC_APB1ENR_enuI2C3EN,
	RCC_APB1ENR_enuReserved13,
	RCC_APB1ENR_enuReserved14,
	RCC_APB1ENR_enuReserved15,
	RCC_APB1ENR_enuReserved16,
	RCC_APB1ENR_enuPWREN,
	RCC_APB1ENR_enuReserved17,
	RCC_APB1ENR_enuReserved18,
	RCC_APB1ENR_enuReserved19,
	RCC_APB1ENR_enuBitsNumber,
}tenuRCC_APB1ENR_Bits;



typedef enum{
	RCC_APB2ENR_enuTIM1EN,
	RCC_APB2ENR_enuReserved00,
	RCC_APB2ENR_enuReserved01,
	RCC_APB2ENR_enuReserved02,
	RCC_APB2ENR_enuUSART1EN,
	RCC_APB2ENR_enuUSART6EN,
	RCC_APB2ENR_enuReserved03,
	RCC_APB2ENR_enuReserved04,
	RCC_APB2ENR_enuADC1EN,
	RCC_APB2ENR_enuReserved05,
	RCC_APB2ENR_enuReserved06,
	RCC_APB2ENR_enuSDIOEN,
	RCC_APB2ENR_enuSPI1EN,
	RCC_APB2ENR_enuSPI4EN,
	RCC_APB2ENR_enuSYSCFGEN,
	RCC_APB2ENR_enuReserved07,
	RCC_APB2ENR_enuTIM9EN,
	RCC_APB2ENR_enuTIM10EN,
	RCC_APB2ENR_enuTIM11EN,
	RCC_APB2ENR_enuReserved08,
	RCC_APB2ENR_enuReserved09,
	RCC_APB2ENR_enuReserved10,
	RCC_APB2ENR_enuReserved11,
	RCC_APB2ENR_enuReserved12,
	RCC_APB2ENR_enuReserved13,
	RCC_APB2ENR_enuReserved14,
	RCC_APB2ENR_enuReserved15,
	RCC_APB2ENR_enuReserved16,
	RCC_APB2ENR_enuReserved17,
	RCC_APB2ENR_enuReserved18,
	RCC_APB2ENR_enuReserved19,
	RCC_APB2ENR_enuReserved20,
	RCC_APB2ENR_enuBitsNumber,
}tenuRCC_APB2ENR_Bits;



typedef enum {
	RCC_enuClkSrcHSI=0,
	RCC_enuClkSrcHSE,
	RCC_enuClkSrcPLL
}RCC_tenuSysClkSrc;

/************RCC clock control register (RCC_CR) Functions************/

rcc_enuErrorStatus_t rcc_setHSION(void);

rcc_enuErrorStatus_t rcc_setHSEON(void);

rcc_enuErrorStatus_t rcc_setPLLON(void);

rcc_enuErrorStatus_t rcc_setPLLI2SON(void);

rcc_enuErrorStatus_t rcc_setHSIOFF(void);

rcc_enuErrorStatus_t rcc_setHSEOFF(void);

rcc_enuErrorStatus_t rcc_setPLLOFF(void);

rcc_enuErrorStatus_t rcc_setPLLI2SOFF(void);

rcc_enuErrorStatus_t rcc_setCSSON(void);

rcc_enuErrorStatus_t rcc_setCSSOFF(void);

rcc_enuErrorStatus_t rcc_setHSEBYPON(void);

rcc_enuErrorStatus_t rcc_setHSEBYPOFF(void);


/************RCC PLL configuration register (RCC_PLLCFGR) Functions************/
/*
 * ARGUMENTS: PLLSRC_HSI PLLSRC_HSE */
rcc_enuErrorStatus_t rcc_setPLLSRC(u8 PLLSRC_);
/*
 * return Add_u8PLLSRC=0 when PLLSRC_HSI
 * return Add_u8PLLSRC=1 when PLLSRC_HSE
 */
rcc_enuErrorStatus_t rcc_getPLLSRC (u8* Add_u8PLLSRC);
rcc_enuErrorStatus_t rcc_configPLLSysClk(u8 PLLQ_, u8 PLLP_, u16 PLLN_,u8 PLLM_);



/************RCC clock configuration register (RCC_CFGR) Functions**************/
/*
 MCO2[1:0]: Microcontroller clock output 2
Set and cleared by software. Clock source selection may generate glitches on MCO2. It is
highly recommended to configure these bits only after reset before enabling the external
oscillators and the PLLs.
00: System clock (SYSCLK) selected
01: PLLI2S clock selected
10: HSE oscillator clock selected
11: PLL clock selected
 */
rcc_enuErrorStatus_t rcc_setMCO2(u32 MCO2_SelClk);
/*
MCO2PRE: MCO2 prescaler
Set and cleared by software to configure the prescaler of the MCO2. Modification of this
prescaler may generate glitches on MCO2. It is highly recommended to change this
prescaler only after reset before enabling the external oscillators and the PLLs.
*/
rcc_enuErrorStatus_t rcc_setMCO2PRE(u8 MCO2DivBy_);
rcc_enuErrorStatus_t rcc_setMCO1PRE(u8 MCO1DivBy_);
/*
 * Set and cleared by software. This bit allows to select the I2S clock source between the
PLLI2S clock and the external clock. It is highly recommended to change this bit only after
reset and before enabling the I2S module.
0: PLLI2S clock used as I2S clock source
1: External clock mapped on the I2S_CKIN pin used as I2S clock source
*/
rcc_enuErrorStatus_t rcc_setI2SSRC(u8 I2SSRC_);
/*
MCO1: Microcontroller clock output 1
Set and cleared by software. Clock source selection may generate glitches on MCO1. It is
highly recommended to configure these bits only after reset before enabling the external
oscillators and PLL.
00: HSI clock selected
01: LSE oscillator selected
10: HSE oscillator clock selected
11: PLL clock selected
*/
rcc_enuErrorStatus_t rcc_setMCO1(u8 MCO1SelClk_);
/*
RTCPRE: HSE division factor for RTC clock
Set and cleared by software to divide the HSE clock input clock to generate a 1 MHz clock
for RTC
*/
rcc_enuErrorStatus_t rcc_setRTCPRE(u8 RTC_HSEDivBy_);


/**
PPRE1: APB Low speed prescaler (APB1)
Set and cleared by software to control APB low-speed clock division factor.
*/
rcc_enuErrorStatus_t rcc_setAPB1_PPRE1(u8 AHBClkDivBy_);
/*PPRE2: APB high-speed prescaler (APB2)
Set and cleared by software to control APB high-speed clock division factor.rcc_enuErrorStatus_t rcc_setAPB2_PPRE(u8 AHBClkDivBy_);
*/

rcc_enuErrorStatus_t rcc_setAPB2_PPRE2(u8 AHBClkDivBy_);

/*
HPRE: AHB prescaler Set and cleared by software to control AHB clock division factor.
Caution: The clocks are divided with the new prescaler factor from 1 to 16 AHB cycles after
HPRE write*/
rcc_enuErrorStatus_t rcc_setAHB_HPRE(u8 SysClkDivBy_);

rcc_enuErrorStatus_t rcc_setSW(u8 SysClk_); //confused bet rcccr and rcc_cfgr
rcc_enuErrorStatus_t rcc_getSWS(u8* Add_RCC_CurrSWS);

/*RCC_AHB1RSTR*/
/*
0: does not reset Bit
1: resets Bit
*/
rcc_enuErrorStatus_t rcc_reset_AHB1RSTR(tenuRCC_AHB1RSTR_Bits RCC_AHB1RSTR_enu );
rcc_enuErrorStatus_t rcc_reset_AHB2RSTR(tenuRCC_AHB2RSTR_Bits RCC_AHB2RSTR_enu);
rcc_enuErrorStatus_t rcc_AHB1ENR_Clk(tenuRCC_AHB1ENR_Bits RCC_AHB1ENR_enu,u32 AHB1ENR_Clk_Mode);
rcc_enuErrorStatus_t rcc_AHB2ENR_Clk(tenuRCC_AHB2ENR_Bits RCC_AHB2ENR_enu,u32 AXBENR_Clk_Mode);


rcc_enuErrorStatus_t rcc_reset_APB1RSTR(tenuRCC_APB1RSTR_Bits RCC_APB1RSTR_enu );
rcc_enuErrorStatus_t rcc_reset_APB2RSTR(tenuRCC_APB2RSTR_Bits RCC_APB2RSTR_enu);
rcc_enuErrorStatus_t rcc_APB1ENR_Clk(tenuRCC_APB1ENR_Bits RCC_APB1ENR_enu,u32 AXBENR_Clk_Mode);
rcc_enuErrorStatus_t rcc_APB2ENR_Clk(tenuRCC_APB2ENR_Bits RCC_APB2ENR_enu,u32 AXBENR_Clk_Mode);



#endif /* __RCC_H__ */
