-list:
	@echo "Available rules:"
	@echo
	@echo "⋅•⋅⋅•⋅ Build Options ⋅•⋅⋅•⋅⊰"
	@echo "  all         - Builds the main target executable ($(NAME))."
	@echo "  bot         - Builds the bot executable ($(BOT_NAME))."
	@echo "  debug       - Builds the debug version of the executable ($(DEBUG_NAME))."
	@echo
	@echo "⋅•⋅⋅•⋅ Cleaning Options ⋅•⋅⋅•⋅⊰"
	@echo "  clean       - Removes all build files and directories."
	@echo "  cleanbot    - Removes bot-related build files."
	@echo "  cleandebug  - Removes debug-related build files."
	@echo "  cleanserv   - Removes server-related build files."
	@echo "  fclean      - Performs a full clean, including executables and logs."
	@echo
	@echo "⋅•⋅⋅•⋅ Debugging Options ⋅•⋅⋅•⋅⊰"
	@echo "  info        - Displays debugging information about variables."
	@echo "  re          - Cleans and rebuilds the main target."
	@echo "  redebug     - Cleans and rebuilds the debug target."
	@echo "  rebot       - Cleans and rebuilds the bot target."
	@echo
	@echo "⋅•⋅⋅•⋅ Execution Options ⋅•⋅⋅•⋅⊰"
	@echo "  drun        - Runs the debug executable with Valgrind."
	@echo "  run         - Runs the main executable with default (4444) or specified (6667) port."
	@echo
	@echo "⋅•⋅⋅•⋅ Formatting Options ⋅•⋅⋅•⋅⊰"
	@echo "  format      - Formats all source files using a formatting script."
