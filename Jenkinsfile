pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                // Checkout the source code from the repository
                checkout scm
            }
        }

        stage('Run git clang-format') {
            steps {
                script {
                    // Run git clang-format and store the result
                    def result = sh(script: 'git clang-format HEAD~1 --diff', returnStdout: true).trim()

                    // Print the result to the console
                    echo "git clang-format output:\n${result}"

                    // Fail the build if clang-format found issues
                    if (result.contains("clang-format did not modify any files")) {
                        echo "No formatting issues detected."
                    }
                }
            }
        }
    }

    post {
        always {
            recordIssues enabledForFailure: true, tool: git-clang-format-parser()
            // Clean up workspace after build
            cleanWs()
        }
    }
}
