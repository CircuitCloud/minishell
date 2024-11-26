// void print_ast(t_command *node, int level) 
// {

//     if (!node)
//         return;
	
//     printf("------- Command: ---------\n\n\n");
// 	// if(node->cmnd)
// 	printf("  %s\n", node->cmnd);
// 	//  printf("(%s)", node->args[0]);
//     if (node && node->args) 
// 	{
// 		int i = 0;
//         printf("arguments : ");
//         while (node ->args && node->args[i]) 
// 		{
//             printf("(%s)", node->args[i]);
// 			i++;
//         }
//         printf("\n");
//     }

//     if (node->redir) 
// 	{
//         printf("rdirections : \n");
// 		while (node->redir)
// 		{
// 			printf("	file :    [%s]\n", node->redir->file);
// 			printf("	delimiii :   /%s\n", node->redir->delimiter);
// 			printf("	delimiiibe4 :   /%s\n", node->redir->delimiter_be4expand);
// 			// printf("	%d\n", node->redir->type);
// 			node->redir= node->redir->next_redir;
// 		}
//         // printf("%s\n", node->redir->file);
//     }
//     if (node->left)
// 	{
//         printf("----------Llllleft:\n");
//         print_ast(node->left, level + 1);
//     }
//     if (node->right) 
// 	{
//         printf("----------Right:\n");
//         print_ast(node->right, level + 1);
//     }
// }