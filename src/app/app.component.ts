import { Component } from '@angular/core';
import { Platform } from 'ionic-angular';
import { StatusBar } from '@ionic-native/status-bar';
import { SplashScreen } from '@ionic-native/splash-screen';

import { TabsPage } from '../pages/tabs/tabs';
import {BackandService} from '../providers/backandService';
import {HomePage} from '../pages/home/home';



@Component({
  template: `<ion-nav [root]="rootPage"></ion-nav>`
})
export class MyApp {
  rootPage: any = TabsPage;
  

  constructor(platform: Platform, private backandService:BackandService) {
    platform.ready().then(() => {
      // Okay, so the platform is ready and our plugins are available.
      // Here you can do any higher level native things you might need.

      //StatusBar.styleDefault();
      backandService.setIsMobile(platform.is('mobile'));
      backandService.setAppName('pillpal');
      backandService.setSignUpToken('d81c9627-821c-4283-90b4-69d4da97fbbf');
      backandService.setAnonymousToken('88bfd02b-0364-4e43-9f14-247e56208dec');
    });
  }
}
