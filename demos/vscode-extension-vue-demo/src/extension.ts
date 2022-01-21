
import * as vscode from 'vscode';

export function activate(context: vscode.ExtensionContext) {
	console.log('Congratulations, your extension "vscode-extension-vue-demo" is now active!');
	let disposable = vscode.commands.registerCommand('extension.helloWorld', () => {
		vscode.window.showInformationMessage('Hello World!1111');
	});

	let createWebview = vscode.commands.registerCommand('extension.createWebview', () => {
		vscode.window.showInformationMessage('createWebview');
	});

	context.subscriptions.push(disposable);
	context.subscriptions.push(createWebview);
	
}

// this method is called when your extension is deactivated
export function deactivate() {}
