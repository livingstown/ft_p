/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:28:43 by jandreu           #+#    #+#             */
/*   Updated: 2019/04/30 17:28:47 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
# define FT_P_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <unistd.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <string.h>
# include <dirent.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>
# include <signal.h>
# include <netinet/tcp.h>
# include "../libft/includes/libft.h"

# define TRANS_SIZE 2047
# define FILE_SIZE 2047
# define RET_KO 1
# define RET_OK 0
# define MAX_TRY 5

# define T_MSG	"<MSG>"
# define T_MSG_OK 0
# define T_MSG_KO 1

# define T_LOG 	"<LOG>"
# define T_CMD 	"<CMD>"

# define T_GET 	"<GET>"
# define T_PUT 	"<PUT>"
# define T_LS  	"<LIS>"
# define T_CD 	"<CWD>"
# define T_PWD 	"<PWD>"
# define T_BYE	"<BYE>"

# define CMD_SIZE 5

# define V_LOGIN "Login"
# define V_PASS "Password"
# define BAD_LOG "Informations de connexions non reconnue"
# define PARAM_MISSING "Il manque un param pour la commande"
# define ERROR_OPEN "Une erreur est survenu dans l'ouverture du dossier"
# define ERROR_EXEC "Une erreur est survenu dans l'execution de la commande"
# define COMMAND_NOT_FOUND "Commande inconnue (ls/cd/pwd/get/put)"
# define ERR_NOTDIR "Un élément du chemin d'accès n'est pas un répertoire"
# define ERR_ACL "Impossible de lire ou de parcourir un composant du chemin"
# define ERR_ENOENT "Le fichier n'existe pas."
# define ERROR_DEFAULT "Une erreur est survenu"
# define ERROR_FILE_RECPT "Une erreur est surevenu dans la récupération"
# define ERR_NAMETOOLONG "Le nom du fichier est trop long"
# define ERR_CD "Retour a la racine"
# define ERR_MAXTRY "Nombre de tentatives maximum atteint"
# define ERR_LISTENSOCK "Erreur dans l'ecoute de la socket"
# define ERR_GETPATH "Merci de donner un nom de fichier et nom un path"
# define ABORT "-1"
# define OK "0"
# define RETRY "1"
# define SERVER 0
# define GOOD_LOG "Login ok !"
# define CWD_OK "Changement du répertoire de travail !"
# define LS_GOOD "Récupération du contenu du répertoire"
# define PWD_GOOD "Récupération du répertoire courant"
# define GET_OK "Téléchargement du fichier terminer"
# define PUT_OK "Upload du fichier terminer"
# define RET_EXIT_FAIL 256

typedef struct			s_trame
{
	uint8_t				type_msg;
	char				type[6];
	char				value[2048];
	int					read;
	int					error;
	off_t				size;
}						t_trame;

typedef struct			s_info
{
	char				*base_path;
	char				*path;
	int					b_path_lvl;
}						t_info;

/*
 **====================== SERVER SIDE
*/
/*
 ** server_command.c
*/
int						manage_command(int cs, t_trame trame, t_info *info);

/*
 ** change_dir.c
*/
void					cd_command(int sock, t_trame trame, t_info *info);
void					format_path(t_info *info, int sock, char *type);
char					*set_path(char *path);

/*
 ** file_operation.c
*/
int						get_command(int sock, t_trame tramef);
int						put_command(int sock, t_trame trame);

/*
 **====================== CLIENT SIDE
*/

/*
 ** cli_command.c
*/
int						parse_command(char **commands, int sock);
void					init_path(t_info *info, int sock);

/*
 ** parse_msg.c
*/
int						parse_msg(t_trame trame, int sock, t_info *info);

/*
 ** commands.c
*/
void					manage_ls(int sock);
int						manage_get(t_trame trame, int sock);

/*
 ** ===================== COMMON
*/

/*
 ** output.c
*/
void					print_error(char *msg);
void					print_succes(char *msg);
void					print_prompt(char *path);
void					print_status_bar(off_t c_size, off_t f_size);
void					usage(char *msg, int src);

/*
 ** send_receive.c
*/
void					send_message(uint8_t type_message, char *value, \
						int sock);
void					send_command(char *type, char *value, int sock, \
						off_t size);
t_trame					listen_sock(int sock);
int						wait_response(int sock);

/*
 ** create_socket.c
*/
int						create_server(int port);
int						create_client(char *addr, int port);

/*
 ** manage_errno.c
*/
char					*get_error();

/*
 ** file_management.c
*/
int						send_file(int fd, int sock, off_t f_size, char *type);
off_t					get_file_size(int fd, int sock);
int						recev_file(int sock, int fd, off_t f_size, char *type);

/*
 ** tools.c
*/
char					*get_name_from_path(char *path);
#endif
