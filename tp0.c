#include "tp0.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();

	log_info(logger,"Soy un log\n");

	config = leer_config();

	valor = config_get_string_value(config,"CLAVE");

	log_info(logger,valor);

	leer_consola(logger);


	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");

	conexion = crear_conexion(ip,puerto);

	enviar_mensaje(valor, conexion);

	t_paquete* paquete = armar_paquete();

	enviar_paquete(paquete, conexion);

	eliminar_paquete(paquete);
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
}




t_log* iniciar_logger(void) {
	// char* file, char *program_name  bool is_active_console, t_log_level
	t_log *logger;
	if ((logger = log_create("tp0.log","TP0",1,LOG_LEVEL_INFO)) == NULL)
	{
		printf("No se pudo crear el logger \n");
		exit(1);
	}
	return logger;
}

t_config* leer_config(void){
	t_config* configuracion;
	if ((configuracion = config_create("tp0.config")) == NULL){
		printf("No se pudo crear configuración");
		exit(2);
	}
	return configuracion;
}

void leer_consola(t_log* logger){
	char* leido;
	leido = readline(">");
	while(*leido != '\0')
	{
		log_info(logger,leido);
		free(leido);
		leido = readline(">");
	}
	free(leido);
}

t_paquete* armar_paquete(){
	t_paquete* paquete = crear_paquete();
	char* leido = readline(">");
	while(*leido != '\0')
	{
		agregar_a_paquete(paquete, leido, strlen(leido)+1);
		free(leido);
		leido = readline(">");
	}
	free(leido);
	return paquete;
}


