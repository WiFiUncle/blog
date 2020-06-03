// Karma configuration
// Generated on Wed Dec 27 2017 11:00:34 GMT+0800 (中国标准时间)

module.exports = function(config) {
  config.set({

    // base path that will be used to resolve all patterns (eg. files, exclude)
    basePath: '',

    plugins: [
        'karma-chrome-launcher',
        'karma-jasmine',
        'karma-webpack',
       // 'karma-sourcemap-loader',
       // 'karma-coverage-istanbul-reporter',
    ],

    // frameworks to use
    // available frameworks: https://npmjs.org/browse/keyword/karma-adapter
    frameworks: ['jasmine'],


    // list of files / patterns to load in the browser
    files: [
    ],


    // list of files / patterns to exclude
    exclude: [
      'What is the location of your source and test files ?',
      'You can use glob patterns, eg. "js/*.js" or "test/**/*Spec.js".',
      'Enter empty string to move to the next question.',
      '>',
      'js/**/*.js',
      'js/**/*.js'
    ],


    // preprocess matching files before serving them to the browser
    // available preprocessors: https://npmjs.org/browse/keyword/karma-preprocessor
    preprocessors: {
      'js/**/*.js': ['webpack', 'sourcemap']
    },

    // webpack配置 不需要入口(entry)和输出(output)配置
    webpack: {
        devtool: 'inline-source-map',
        module: {
            rules: [{
                test: /\.js$/,
                use: {
                    loader: 'istanbul-instrumenter-loader',
                    options: { esModules: true }
                },
                enforce: 'pre',
                exclude: /node_modules|\.spec\.js$/,
            }, {
                test: /\.js$/,
                use: {
                    loader: 'babel-loader',
                    options: {
                        presets: ['es2015'],
                        plugins: ['istanbul']
                    }
                },
                exclude: /node_modules/
            }]
        }
    },
    // test results reporter to use
    // possible values: 'dots', 'progress'
    // available reporters: https://npmjs.org/browse/keyword/karma-reporter
    reporters: ['progress'],


    // web server port
    port: 9876,


    // enable / disable colors in the output (reporters and logs)
    colors: true,


    // level of logging
    // possible values: config.LOG_DISABLE || config.LOG_ERROR || config.LOG_WARN || config.LOG_INFO || config.LOG_DEBUG
    logLevel: config.LOG_INFO,


    // enable / disable watching file and executing tests whenever any file changes
    autoWatch: true,


    // start these browsers
    // available browser launchers: https://npmjs.org/browse/keyword/karma-launcher
    browsers: ['Chrome'],


    // Continuous Integration mode
    // if true, Karma captures browsers, runs the tests and exits
    singleRun: false,

    // Concurrency level
    // how many browser should be started simultaneous
    concurrency: Infinity,


  })
}
