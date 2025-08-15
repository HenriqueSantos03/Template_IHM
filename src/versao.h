#ifndef VERSAO_H_
#define VERSAO_H_

//*******************************************************************************************
// constantes de versoes/debugers
//*******************************************************************************************

//#define DEBUG_ENERGY      // exibe informação para debugar capturas/conversões
//#define DEBUG_KEYBOARD    // exibe informação para debugar capturas/conversões

//#if defined(LINUX) || defined(ANDROID)
#if defined(DEBUG_KEYBOARD) || defined(DEBUG_ENERGY)
#define  DEBUG_ATIVO
#endif

//*******************************************************************************************
// Detalhes das versões
//*******************************************************************************************

//----------------VERSAO ATUAL----------------------------------------
#ifndef  DEBUG_ATIVO
#define VERSAO_FIRMWARE    "V 1.0.0"    // versao normal
#else
#define VERSAO_FIRMWARE    "V 1.0.0d"    // versao com algum debug ativo
#endif
// data: 27/06/2024
// versão: 1.0.0
// descrição/alterações: 
//  - versão inicial
//----------------HISTORICO----------------------------------------

#endif /* versao.h */
