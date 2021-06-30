#include "Enge_PCH.h"

#include "Application.h"

int main() {
	
	Enge::Application engineApp;
	int initState = engineApp.ApplicationInit();
	
	if (initState == EXIT_FAILURE) {
		LOG_ERR("FATAL_ERROR::APPLICATION::APPLICATION_COULD_NOT_BE_STARTED::IMAGINE_SUCKING\n");
		return -1;
	}

}
