import { Component, OnInit } from '@angular/core';
import { DomSanitizer } from '@angular/platform-browser';
import { ApiService } from '../../services/api.service';
import {environment} from "../../../environments/environment";

// uncomment the following import in order to use Lodash
// import * as _ from 'lodash';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.scss']
})
export class HomeComponent implements OnInit {
  screenshot: any;

  constructor(private apiService: ApiService, private sanitizer: DomSanitizer) {
  }

  ngOnInit(): void {
    this.apiService.getScreenshot().subscribe((data: any) => {
      const objectURL = 'data:image/bmp;base64,' + data.Image;
      this.screenshot = this.sanitizer.bypassSecurityTrustUrl(objectURL);
    }, (err) => {
      console.log('HttpErrorResponse error occured.');
    });
  }
}
