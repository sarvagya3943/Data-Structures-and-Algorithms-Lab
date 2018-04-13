#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <curl/curl.h>

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

int save_file(const char *webfilename,const char *url,CURL *curl_handle)
{
  FILE *webfile;

  /* set url */
  curl_easy_setopt(curl_handle, CURLOPT_URL,url);

  /* no progress meter please */
  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);

  /* send all data to this function  */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

  /* open the web file */
  webfile = fopen(webfilename, "wb");
  if(!webfile) {
    return -1;
  }

  /* we want the body be written to this file handle instead of stdout */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, webfile);

  /* get it! */
  curl_easy_perform(curl_handle);

  /* close the web file */
  fclose(webfile);

  return 0;
}
