# invoke SourceDir generated makefile for RTOS_config.pem4f
RTOS_config.pem4f: .libraries,RTOS_config.pem4f
.libraries,RTOS_config.pem4f: package/cfg/RTOS_config_pem4f.xdl
	$(MAKE) -f D:\manchini\projetos\ppgca_embedded_TM4C_websocket_client/src/makefile.libs

clean::
	$(MAKE) -f D:\manchini\projetos\ppgca_embedded_TM4C_websocket_client/src/makefile.libs clean

