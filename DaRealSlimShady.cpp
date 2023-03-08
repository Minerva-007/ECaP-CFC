#include"stdio.h"
#include"stdlib.h"
#include"unistd.h"

int main()
{
	system("clear");
	printf("With everlasting love for the Dokis <3\n");
	printf("Carbon Footprint Calculating Daemon, by Minerva_007\n");
	printf("---------------------------------------------------\n");
	// Save the skip count in a file
	FILE *index = fopen("INDEX","r");
	int C=0;
	fscanf(index, "%d", &C);
	fclose(index);
	while(1)
	{
		printf("Fetching data\n");
		system("python3 getsheets.py");
		//This gets all the data into List.txt
		printf("Opening File\n");
		FILE* f = fopen("List.txt","r");
		//Skip C records
		char response[60];
		for(int i=0;i<C;i++)
		{
			for(int j=0;j<11;j++)
				fscanf(f, "%s", response);
		}
		printf("Skipped %d records\n",C);
		//For each new record, increment C and shoot an email.
		save:
		while(!feof(f))
		{
			//Read the details
			//And copy into input.txt
			sleep(3);
			FILE *input = fopen("input.txt","w");
			printf("User data received:\n");
			for(int i=0;i<11;i++)
			{
				if(feof(f))
				{
					goto save;
				}
				fscanf(f, "%s", response);
				printf("%s\n", response);
				fprintf(input, "%s\n", response);
			}
			printf("---------------------------\n");
			//Save the file
			fclose(input);
			// Call Calc.py and wait for response
			system("python3 Calc.py");
			// Results are saved in output.txt
			FILE *output = fopen("output.txt", "r");
			float CO2;
			fscanf(output,"%s%f",response,&CO2);
			fclose(output);
			//Write the email
			output = fopen("content.txt","w");
			fprintf(output, "Dear participant,\n\nThank you for submitting your daily preferences.\n Based on the information provided, we have calculated your average carbon footprint to be %2.2f tonnes of CO2 per year.\n The average carbon footprint of a human being is 4.8 tonnes of CO2 equivalent per year.\n\n",CO2);
			if(CO2<4.8)
			{
				//Use a good message
				fprintf(output,"We are pleased to inform you that your carbon footprint is below the average.\n Congratulations on taking steps towards a sustainable lifestyle!\n However, there are always opportunities to improve, and we encourage you to continue your efforts to reduce your carbon footprint.\n\n");
				fprintf(output,"We have attached a pamphlet to this email that provides information on how you can further reduce your carbon footprint.\n Please take a moment to review it and feel free to reach out to us if you have any questions.\n\n");
				fprintf(output,"Thank you for your commitment to sustainability.\nThanks and regards\nECAP 2023 Team\n\n");
				fprintf(output,"\n\n\nMaintained with <3 by Nerd Gang from UET weeb Union");
			}
			else
			{
				//Use a bad message
				fprintf(output,"If your carbon footprint is above the average, it is an alarming situation that needs immediate attention.\n Climate change and global warming are real and every human counts towards reducing carbon emissions.\n It is our responsibility to take action and make changes towards a sustainable lifestyle.\n\n");
				fprintf(output,"We have attached a pamphlet as a guide towards a sustainable lifestyle.\n We highly recommend you to follow the tips mentioned in the pamphlet to reduce your carbon footprint and contribute towards a cleaner environment.\n\n");
				fprintf(output,"Thank you for taking the initiative to learn about your carbon footprint. Together, we can make a difference.\n\n");
				fprintf(output,"Best Regards\nECAP 2023 Team\n");
				fprintf(output,"\n\n\nMaintained with <3 by Nerd Gang from UET weeb Union");
			}
			fclose(output);
			//Transfer control to sendmail2
			sleep(3);
			system("python3 sendmail2.py");
			printf("-------------------------------------\n");
			C++;
		}
		fclose(f);
		index=fopen("INDEX","w");
		fprintf(index,"%d",C);
		fclose(index);
		printf("Halting for 10s\n");
		sleep(60);
	}
	return 0;
}	
