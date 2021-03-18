import {Injectable} from '@angular/core';
import {HttpClient} from '@angular/common/http';
import { environment } from '../../environments/environment';
import {SafeResourceUrl} from "@angular/platform-browser";

@Injectable({
  providedIn: 'root'
})
export class ApiService {
  public url: SafeResourceUrl;

  constructor(private httpClient: HttpClient) { }

  public getNews(){
    return this.httpClient.get(environment.apiUrl + `users/all`);
  }

  public getScreenshot() {
    return this.httpClient.get(environment.apiUrl + `users/screen`);
  }

}
