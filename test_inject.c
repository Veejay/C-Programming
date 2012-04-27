#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct User {
  char *first_name;
  char *last_name;
  char *email;
  char *password;
  time_t created_at;
  time_t updated_at;
};

typedef struct User User;

char* format_time(time_t t)
{
  char *formatted_time = malloc(64 * sizeof(char));
  struct tm *ts = localtime(&t);
  strftime(formatted_time, (size_t)64, "%Y-%m-%d", ts);
  return formatted_time; 
}

char* jsonify(User u){
  char *result = malloc(1024 * sizeof(char));
  char* updated = format_time(u.updated_at);
  char* created = format_time(u.created_at);

  asprintf(&result, 
      "{\n\tfirst_name: \"%s\",\n\tlast_name: \"%s\",\n\temail: \"%s\",\n\tpassword: \"%s\",\n\tcreated_at: %s,\n\tupdated_at: %s\n}",
      u.first_name, 
      u.last_name, 
      u.email, 
      u.password, 
      updated, 
      created
      );
  free(updated);
  free(created);
  return result;
}

int main()
{
  User u;
  
  u.first_name = "Bertrand";
  u.last_name  = "Chardon";
  u.email      = "bertrand.chardon@gmail.com";
  u.password   = "secret";
  u.created_at = time(0);
  u.updated_at = time(0);
  
  char *json = jsonify(u);

  printf("JSON version of the User record:\n %s\n", json);
  free(json);
  return 0;
}
