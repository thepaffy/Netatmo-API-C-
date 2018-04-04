pipeline {
    agent {
        dockerfile {
            dir 'image'
        }
    }
    stages {
        stage('Build') {
            steps {
                sh 'mkdir build'
                dir('build') {
                    sh 'cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_INSTALL_PREFIX=$WORKSPACE/install/usr -DBUILD_DOCUMENTATION=ON ..'
                    sh 'make -j6'
                    warnings canComputeNew: false, canResolveRelativePaths: false, categoriesPattern: '', consoleParsers: [[parserName: 'Clang (LLVM based)']], defaultEncoding: '', excludePattern: '', healthy: '', includePattern: '', messagesPattern: '', unHealthy: ''
                    sh 'make docs'
                    publishHTML([allowMissing: false, alwaysLinkToLastBuild: false, keepAll: false, reportDir: 'doc/netatmo++-html/', reportFiles: 'index.html', reportName: 'Netatmo++ API', reportTitles: ''])
                    sh 'make install'
                }
            }
        }
        stage('Analyze') {
            steps {
                sh 'mkdir analyze'
                dir('analyze') {
                    sh 'cmake -DCMAKE_C_COMPILER=/usr/lib/clang/ccc-analyzer -DCMAKE_CXX_COMPILER=/usr/lib/clang/c++-analyzer ..'
                    sh 'scan-build -o ../scan make -j 6 -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-unused-macros -Wno-newline-eof -Wno-exit-time-destructors -Wno-global-constructors -Wno-gnu-zero-variadic-macro-arguments -Wno-documentation -Wno-shadow -Wno-switch-enum -Wno-missing-prototypes -Wno-used-but-marked-unused -Wno-unknown-pragmas'
                }
            }
        }
        stage('Test') {
            steps {
                withCredentials([usernamePassword(credentialsId: 'f6e2df87-5109-4877-a313-00f1c53f979f', passwordVariable: 'TEST_PASSWORD', usernameVariable: 'TEST_USERNAME'), usernamePassword(credentialsId: '9e5f4048-8211-49b5-949b-aa8b66feb6fd', passwordVariable: 'TEST_CLIENTSECRET', usernameVariable: 'TEST_CLIENTID')]) {
                    dir('build/tests') {
                        sh 'ctest --no-compress-output -T Test || /usr/bin/true'
                        step([$class: 'XUnitPublisher', testTimeMargin: '3000', thresholdMode: 1, thresholds: [[$class: 'FailedThreshold', failureNewThreshold: '', failureThreshold: '', unstableNewThreshold: '', unstableThreshold: ''], [$class: 'SkippedThreshold', failureNewThreshold: '', failureThreshold: '', unstableNewThreshold: '', unstableThreshold: '']], tools: [[$class: 'CTestType', deleteOutputFiles: true, failIfNotNew: true, pattern: 'build/tests/Testing/**/Test.xml', skipNoTestFiles: false, stopProcessingIfError: true]]])
                    }
                }
            }
        }
        stage('Finish') {
            steps {
                archiveArtifacts 'install/usr/**/*'
                emailext attachLog: true, body: '''${JOB_NAME} - Build # ${BUILD_NUMBER} - ${currentBuild.result}:

Check console output at ${currentBuild.absoluteUrl} to view the results.''', recipientProviders: [developers()], subject: '${JOB_NAME} - Build # ${BUILD_NUMBER} - ${currentBuild.result}'
            }
        }
    }
}
