all:
	$(MAKE) -C ./philo_one
	$(MAKE) -C ./philo_two
	$(MAKE) -C ./philo_three

fclean:
	$(MAKE) fclean -C ./philo_one
	$(MAKE) fclean -C ./philo_two
	$(MAKE) fclean -C ./philo_three

re:
	$(MAKE) re -C ./philo_one
	$(MAKE) re -C ./philo_two
	$(MAKE) re -C ./philo_three
