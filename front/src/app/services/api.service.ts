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

  public getScreenshot() {
    return this.httpClient.get(environment.apiUrl + `entryPoint/screen`);
  }

}
